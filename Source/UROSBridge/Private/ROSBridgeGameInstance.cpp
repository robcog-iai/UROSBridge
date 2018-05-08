// Fill out your copyright notice in the Description page of Project Settings.

#include "ROSBridgeGameInstance.h"

void UROSBridgeGameInstance::OnStart()
{
	Super::OnStart();

	UE_LOG(LogROS, Warning, TEXT("OnStart() of GameInstance"));
	//UE_LOG(LogROS, Log, TEXT("[%s] Websocket server connected."), *FString(__FUNCTION__));
	if (!bConnectToROS) {
		UE_LOG(LogTemp, Warning, TEXT("ConnectToROS is false in GameInstance settings. Don't connect to rosbridge..."));
		return;
	}

	ROSHandler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(ROSBridgeServerHost, ROSBridgeServerPort));

	ROSHandler->Connect();

}

void UROSBridgeGameInstance::Tick(float DeltaTime) {
	UE_LOG(LogROS, Warning, TEXT("Tick() of GameInstance"));
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