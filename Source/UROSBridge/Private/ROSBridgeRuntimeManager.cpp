// Fill out your copyright notice in the Description page of Project Settings.

#include "ROSBridgeRuntimeManager.h"
#include "Engine.h"


// Sets default values
AROSBridgeRuntimeManager::AROSBridgeRuntimeManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AROSBridgeRuntimeManager::BeginPlay()
{
	Super::BeginPlay();

	if (!RefSingelton && GEngine)
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



	// Register Services, Publisher and Subcriber 
	for (auto Pub : PublisherList)
	{
		if (Pub)
		{
			// Make sure it's renamed, even if its pulished already, to get refrence to copied object in active world
			auto BaseClass = Pub->GetDefaultObject<UROSPublisherBaseClass>();
			OldOuterMap.Add(Pub->GetName(), BaseClass->GetOuter());
			BaseClass->Rename(*BaseClass->GetName(), this);

			if (AlreadyRegistered.Find(Pub) == INDEX_NONE)
			{

				
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
	}

	bool b1 = (RosHandler->GetHost().Compare(ServerAdress) != 0);
	bool b2 = (static_cast<int>(RosHandler->GetPort()) != ServerPort);
	bool bAdressChanged = b1 || b2;
	if(b1 && b2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Both True"));
	} 
	else if (b1)
	{
		UE_LOG(LogTemp, Warning, TEXT("B1 True"));

	}
	else if (b2)
	{
		UE_LOG(LogTemp, Warning, TEXT("B2 True"));
	}
	//bool bAdressChanged = (RosHandler->GetHost().Compare(ServerAdress) != 0) || (static_cast<int>(RosHandler->GetPort()) != ServerPort);
	// Set up Serveradress and callbacks
	RosHandler->AddToUserConnectedCallbacks(this, &AROSBridgeRuntimeManager::ConnectedCallback);
	RosHandler->AddToUserErrorCallbacks(this, &AROSBridgeRuntimeManager::ConnectionErrorCallback);

	// Connect
	if (!RosHandler->IsClientConnected() || b1 || b2)
	{
		RosHandler->SetHost(ServerAdress);
		RosHandler->SetPort(ServerPort);
		RosHandler->Connect();
	}


}

void AROSBridgeRuntimeManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto Pub : PublisherList)
	{
		if (Pub)
		{
			// Make sure Outer is set back to outer from before begin play.
			auto BaseClass = Pub->GetDefaultObject<UROSPublisherBaseClass>();
			FString Name = Pub->GetName();
			UObject* OldOuter = *OldOuterMap.Find(Name);
			OldOuter->GetWorld();
			if (OldOuter) BaseClass->Rename(*BaseClass->GetName(), OldOuter);
			//BaseClass->Rename(*BaseClass->GetName(), *OldOuterMap.Find(Pub->GetName()));
		}

	}
}

// Called every frame
void AROSBridgeRuntimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



UWorld* AROSBridgeRuntimeManager::GetWorld() const
{
	// CDO objects do not belong to a world
	// If the actors outer is destroyed or unreachable we are shutting down and the world should be NULL
	if (!HasAnyFlags(RF_ClassDefaultObject) && !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (ULevel* Level = GetLevel())
		{
			return Level->OwningWorld;
		}
	}
	return nullptr;
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