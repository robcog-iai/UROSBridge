// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ROSPublisherBaseClass.h"
#include "ROSBridgeHandler.h"
#include "RosBridgeHandlerRefSingleton.h"
#include "ROSBridgeRuntimeManager.generated.h"

UCLASS()
class UROSBRIDGE_API AROSBridgeRuntimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AROSBridgeRuntimeManager();

	UPROPERTY(VisibleInstanceOnly, Category = "RosBridge Websocket")
	FString ConnectionStatus = TEXT("Not connected.");
	UPROPERTY(EditAnywhere, Category = "RosBridge Websocket")
	FString ServerAdress = TEXT("127.0.0.1");
	UPROPERTY(EditAnywhere, Category = "RosBridge Websocket")
	int ServerPort = 9090;


	UPROPERTY(EditAnywhere, Category = "ROS")
	FString Namespace = TEXT("unreal");


	UPROPERTY(EditAnywhere, Category = "ROS")
	TArray<TSubclassOf<UROSPublisherBaseClass>> PublisherList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UWorld* GetWorld() const override;


	void ConnectionErrorCallback();
	void ConnectedCallback();


	UPROPERTY()
	URosBridgeHandlerRefSingleton* RefSingelton;
	UPROPERTY()
	TArray<TSubclassOf<UROSPublisherBaseClass>> AlreadyRegistered;
private:

	TSharedPtr<FROSBridgeHandler>  RosHandler;
	UPROPERTY()
	TMap<FString, UObject*> OldOuterMap;
};
