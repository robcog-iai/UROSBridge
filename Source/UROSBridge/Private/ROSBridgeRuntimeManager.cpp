// Fill out your copyright notice in the Description page of Project Settings.

#include "ROSBridgeRuntimeManager.h"
#include "Engine.h"
#include "RosBridgeHandlerRefSingleton.h"


// Sets default values
AROSBridgeRuntimeManager::AROSBridgeRuntimeManager()
{
	PrimaryActorTick.bCanEverTick = false;

	URosBridgeHandlerRefSingleton* RefSingelton = nullptr;
	if (GEngine)
		RefSingelton = Cast<URosBridgeHandlerRefSingleton>(GEngine->GameSingleton);

	if (!RefSingelton)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]: GameSingleton is not set. New Handler Instance will be created, this might lead to multiple Handler instances/ Ros Connections"), *FString(__FUNCTION__));
		RosHandler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(ServerAdress, ServerPort));
	}
	else
	{
		RosHandler = RefSingelton->GetHandlerRef();
	}

}

// Called when the game starts or when spawned
void AROSBridgeRuntimeManager::BeginPlay()
{
	Super::BeginPlay();

	// Register Services, Publisher and Subcriber 
	for (auto Pub : PublisherList)
	{
		if (Pub)
		{

			auto BaseClass = Pub->GetDefaultObject<UROSPublisherBaseClass>();
			BaseClass->Rename(*BaseClass->GetName(), this);
			BaseClass->Init(Namespace);

			// Register SrvServers
			for (auto SrvServer : BaseClass->ServicesToPublish)
			{
				RosHandler->AddServiceServer(SrvServer);
			}

			// Register Publisher
			for (auto Publisher : BaseClass->PublisherToPublish)
			{
				RosHandler->AddPublisher(Publisher);
			}

			// Register Subscriber
			for (auto Subscriber : BaseClass->SubscriberToPublish)
			{
				RosHandler->AddSubscriber(Subscriber);
			}
		}
	}

	bool bAdressChanged = (RosHandler->GetHost() != ServerAdress) || (RosHandler->GetPort() != ServerPort);
	// Set up Serveradress and callbacks
	RosHandler->SetHost(ServerAdress);
	RosHandler->SetPort(ServerPort);
	RosHandler->AddToUserConnectedCallbacks(this, &AROSBridgeRuntimeManager::ConnectedCallback);
	RosHandler->AddToUserErrorCallbacks(this, &AROSBridgeRuntimeManager::ConnectionErrorCallback);

	// Connect
	if (!RosHandler->IsClientConnected() || bAdressChanged)
	{
		RosHandler->Connect();
	}


}

// Called every frame
void AROSBridgeRuntimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AROSBridgeRuntimeManager::ConnectionErrorCallback()
{
	//AlreadyRegistered.Empty();
	ConnectionStatus = TEXT("Not connected.");
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Connection to RosBridge lost.")));
}

void AROSBridgeRuntimeManager::ConnectedCallback()
{
	ConnectionStatus = TEXT("Connected to Rosbridge.");
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("You are now connected to RosBridge.")));
}