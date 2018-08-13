#include "UROSBridgeEdTool.h"
#include "UObject/ConstructorHelpers.h"
#include "RosBridgeHandlerRefSingleton.h"
#include "LevelEditor.h"
#include "Editor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UUROSBridgeEdTool::UUROSBridgeEdTool(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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



void UUROSBridgeEdTool::ConnectToRosBridge()
{

	AROSBridgeRuntimeManager* RuntimeManager = GetRuntimeManager();

	// Register Services, Publisher and Subcriber 
	for (auto Pub : PublisherList)
	{

		//This Avoids registering the same Servers Multiple times
		if (Pub && AlreadyRegistered.Find(Pub) == INDEX_NONE)
		{
			AlreadyRegistered.Add(Pub);

			auto BaseClass = Pub->GetDefaultObject<UROSPublisherBaseClass>();

			// Make sure Outer is something GetWorld() can be called on.
			if (RuntimeManager)
			{
				BaseClass->Rename(*BaseClass->GetName(), RuntimeManager);
			}
			else
			{
				BaseClass->Rename(*BaseClass->GetName(), this);
			}


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

	// Set up Serveradress and callbacks
	RosHandler->SetHost(ServerAdress);
	RosHandler->SetPort(ServerPort);
	RosHandler->AddToUserConnectedCallbacks(this, &UUROSBridgeEdTool::ConnectedCallback);
	RosHandler->AddToUserErrorCallbacks(this, &UUROSBridgeEdTool::ConnectionErrorCallback);

	// Connect
	if (!RosHandler->IsClientConnected())
	{
		RosHandler->Connect();
	}

}


#if WITH_EDITOR
void UUROSBridgeEdTool::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	AROSBridgeRuntimeManager* RuntimeManager = GetRuntimeManager();

	if (RuntimeManager)
	{
		if (PropertyName == GET_MEMBER_NAME_CHECKED(UUROSBridgeEdTool, ServerAdress))
		{
			RuntimeManager->ServerAdress = ServerAdress;
		}
		else if (PropertyName == GET_MEMBER_NAME_CHECKED(UUROSBridgeEdTool, ServerPort))
		{
			RuntimeManager->ServerPort = ServerPort;
		}
		else if (PropertyName == GET_MEMBER_NAME_CHECKED(UUROSBridgeEdTool, Namespace))
		{
			RuntimeManager->Namespace = Namespace;
		}
		else if (PropertyName == GET_MEMBER_NAME_CHECKED(UUROSBridgeEdTool, bSharePublishers))
		{

			if (bSharePublishers)
			{
				// Sharing now active
				for (auto Pub : PublisherList)
				{
					RuntimeManager->PublisherList.AddUnique(Pub);
				}
			}
			else
			{
				// Sharing deactivated

				for (auto Pub : PublisherList)
				{
					if (Pub && RuntimeManager->PublisherList.Remove(Pub) > 0)
						UE_LOG(LogTemp, Log, TEXT("[%s]: '%s' was removed from RuntimeMangers Publisherlist."),
							*FString(__FUNCTION__), *Pub->GetName());
				}

			}
		}
	}
}

void UUROSBridgeEdTool::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{

	AROSBridgeRuntimeManager* RuntimeManager = GetRuntimeManager();

	if (bSharePublishers && RuntimeManager)
	{
		RuntimeManager->PublisherList = PublisherList;
	}

	Super::PostEditChangeChainProperty(e);
}
#endif



void UUROSBridgeEdTool::ConnectionErrorCallback()
{
	//AlreadyRegistered.Empty();
	ConnectionStatus = TEXT("Not connected.");
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Connection to RosBridge lost.")));
}

void UUROSBridgeEdTool::ConnectedCallback()
{
	ConnectionStatus = TEXT("Connected to Rosbridge.");
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("You are now connected to RosBridge.")));
}

UWorld* UUROSBridgeEdTool::GetWorld() const
{
	if (GEditor)
		return GEditor->GetEditorWorldContext().World();
	return nullptr;

}

AROSBridgeRuntimeManager* UUROSBridgeEdTool::GetRuntimeManager() const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GEditor->GetEditorWorldContext().World(), AROSBridgeRuntimeManager::StaticClass(), FoundActors);
	if (FoundActors.Num() == 1)
	{
		return StaticCast<AROSBridgeRuntimeManager*>(FoundActors.Pop());
	}
	else if (FoundActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]: No AROSRuntimeManger is placed in the world, this means URosBridge cannot effect the world during runtime."), *FString(__FUNCTION__));
	}
	else
	{
		//More then one Runtime Manager found.
		UE_LOG(LogTemp, Error, TEXT("[%s]: More then one AROSRuntimeManger is placed in the world, UROSBridge does only work properly if there is exactly one AROSRuntimeManger."), *FString(__FUNCTION__));
	}
	return nullptr;
}
