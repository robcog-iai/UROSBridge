// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROSBridgeHandler.h"
#include "RosBridgeHandlerRefSingleton.generated.h"

/**
 * This Class is meant to be used as GameSingleton and holds a Hander refrence.
 * To achive this, make an blueprint of this class and set it as GameSinglton in the Project Settings.
 * Project Settings->Engine->General Settings->Default Classes.
 * You need to use the eye icon to show advanced settings.
 * Be sure to select the blueprint version, not the cpp base class.
 * 
 * Once this is set up you can access this class in any c++ code with:
 * 
 * auto RefSingelton = Cast<URosBridgeHandlerRefSingleton>(GEngine->GameSingleton);
 * 
 * If you want a Handler refrence at game time only, use ROSBridgeGameInstance instead.
 */

UCLASS(Blueprintable, BlueprintType)
class UROSBRIDGE_API URosBridgeHandlerRefSingleton : public UObject
{
	GENERATED_BODY()
public:

	URosBridgeHandlerRefSingleton(){};
	~URosBridgeHandlerRefSingleton(){};

	/*
	 * Returns pointer to Handler instance (never Null). 
	 * Note: As this Handler can be accessed by anyone, it might be running/connected, already.
	 */
	TSharedPtr<FROSBridgeHandler> GetHandlerRef();

private:
	TSharedPtr<FROSBridgeHandler> Handler;

};
