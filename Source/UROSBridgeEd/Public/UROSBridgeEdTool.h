#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UROSBridgeEdMode.h"
#include <ROSPublisherBaseClass.h>
#include "ROSBridgeHandler.h"
#include "ROSBridgeRuntimeManager.h"
#include "UROSBridgeEdTool.generated.h"

class FUROSBridgeEdMode;

UCLASS()

class UUROSBridgeEdTool : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	FUROSBridgeEdMode* ParentMode;

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

	/* If true, the publisher list will be shared with the Runtime Manager.
	 * Turn off if you wish to publish diffrent list of publishers during runtime.*/
	UPROPERTY(EditAnywhere, Category = "ROS")
	bool bSharePublishers = true;
	
	UFUNCTION(Exec)
	void ConnectToRosBridge();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;
	
	void SetParent(FUROSBridgeEdMode* NewParent)
	{
		ParentMode = NewParent;
	}

	void ConnectionErrorCallback();
	void ConnectedCallback();

	UWorld* GetWorld() const override;

private:
	UPROPERTY()
	TArray<TSubclassOf<UROSPublisherBaseClass>> AlreadyRegistered;
	UPROPERTY()
	URosBridgeHandlerRefSingleton* RefSingelton;
	TSharedPtr<FROSBridgeHandler>  RosHandler;

	AROSBridgeRuntimeManager* GetRuntimeManager() const;

};
