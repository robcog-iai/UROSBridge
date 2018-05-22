// Fill out your copyright notice in the Description page of Project Settings.

#include "ROSBridgeGameInstance.h"

void UROSBridgeGameInstance::OnStart()
{
	Super::OnStart();

	if (!bConnectToROS) {
		UE_LOG(LogTemp, Warning, TEXT("ConnectToROS is false in GameInstance settings. Don't connect to rosbridge..."));
		return;
	}

	UE_LOG(LogROS, Log, TEXT("Connecting to %s:%d via GameInstance"), *ROSBridgeServerHost, ROSBridgeServerPort);
	ROSHandler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(ROSBridgeServerHost, ROSBridgeServerPort));

	ROSHandler->Connect();

}

void UROSBridgeGameInstance::Tick(float DeltaTime) {
	if (ROSHandler.IsValid())
		ROSHandler->Process();

	return;
}
bool UROSBridgeGameInstance::IsTickable() const {
	return true;
}
TStatId UROSBridgeGameInstance::GetStatId() const {
	return Super::GetStatID();
}

void UROSBridgeGameInstance::Shutdown() {
	if (ROSHandler.IsValid())
		ROSHandler->Disconnect();

	Super::Shutdown();
}