// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#include "ROSBridgeGameInstance.h"

// Default constructor
UROSBridgeGameInstance::UROSBridgeGameInstance()
{
	// ROSBridgeServerHost = "127.0.0.1";
	// ROSBridgeServerPort = 9090;
	bConnectToROS = true;
}

// Called when the game instance is started either normally or through PIE
void UROSBridgeGameInstance::OnStart()
{
	Super::OnStart();

	if (!bConnectToROS)
	{
		UE_LOG(LogTemp, Warning, TEXT("ConnectToROS is false in GameInstance settings. Don't connect to rosbridge..."));
		return;
	}

	UE_LOG(LogROS, Log, TEXT("Connecting to %s:%d via GameInstance"), *ROSBridgeServerHost, ROSBridgeServerPort);
	ROSHandler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(ROSBridgeServerHost, ROSBridgeServerPort));

	ROSHandler->Connect();
}

// Cleanup opportunity when shutting down
void UROSBridgeGameInstance::Shutdown()
{
	if (ROSHandler.IsValid())
	{
		ROSHandler->Disconnect();
	}
	Super::Shutdown();
}

void UROSBridgeGameInstance::Tick(float DeltaTime)
{
	if (ROSHandler.IsValid())
	{
		ROSHandler->Process();
	}
}

bool UROSBridgeGameInstance::IsTickable() const
{
	return true;
}

TStatId UROSBridgeGameInstance::GetStatId() const
{
	return Super::GetStatID();
}
