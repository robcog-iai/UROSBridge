// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UROSBridgeEdMode.h"
#include "UROSCallbackRegisterBase.h"
#include "ROSBridgeHandler.h"
#include "UROSBridgeEdTool.generated.h"

class FUROSBridgeEdMode;

UCLASS()
class UROSBridgeEdTool : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	FUROSBridgeEdMode* ParentMode;

	UPROPERTY(VisibleInstanceOnly, Category = "Network parameter")
	FString ConnectionStatus = TEXT("Not connected.");
	
	/* Adress of the RosBridge Websocket */
	UPROPERTY(EditAnywhere, Category = "Network parameter")
	FString ServerAdress = TEXT("127.0.0.1");

	/* Port of the RosBridge Websocket */
	UPROPERTY(EditAnywhere, Category = "Network parameter")
	int ServerPort = 9090;

	/* Namespace under which all calbacks are registerd in ROS.*/
	UPROPERTY(EditAnywhere, Category = "Callbacks")
	FString Namespace = TEXT("unreal");

	/* 
	  List of Callbacks that get registered when Connect button is clicked. 
	  When adding Callbacks after a connection was established, you need to click Connect again to register the new callbacks.
	*/
	UPROPERTY(EditAnywhere, Category = "Callbacks")	
	TArray<TSubclassOf<UROSCallbackRegisterBase>> PublisherList;


	UFUNCTION(Exec)
	void Disconnect();

	/* 
	  Connect to Websocket and register Callbacks listed below.
	  This button can be clicked again to register callbacks added to the list after initial connection.
	*/
	UFUNCTION(Exec)
	void Connect();

		
	void SetParent(FUROSBridgeEdMode* NewParent)
	{
		ParentMode = NewParent;
	}

	void ConnectionErrorCallback();
	void ConnectedCallback();

	UWorld* GetWorld() const override;

private:
	UPROPERTY()
	TArray<TSubclassOf<UROSCallbackRegisterBase>> AlreadyRegistered;
	TSharedPtr<FROSBridgeHandler> RosHandler;

};
