// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ROSBridgeSrvServer.h"
#include "ROSBridgePublisher.h"
#include "ROSBridgeSubscriber.h"
#include "UROSCallbackRegisterBase.generated.h"

/**
 * This class is essentially an Interface. It is not meant to be instantiated.
 * An actuall interface could not be used, because Editor selection does not support
 * arrays of an interfaces type.
 */

UCLASS(abstract)
class UROSBRIDGEED_API UROSCallbackRegisterBase : public UObject
{
	GENERATED_BODY()

public:
	UROSCallbackRegisterBase(){}
	~UROSCallbackRegisterBase() {}

	/* 
	 * After call to this function the Arrays are expected to be set up correctly.
	 * If Namespace is not needed, just ignore it. It will always be provided.
	 */
	virtual void Register(FString DefaultNamespace)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s]: This function schould be overriden by derived class. This class is meant to function like an Interface."), *FString(__FUNCTION__));
	};

	TArray<TSharedPtr<FROSBridgeSrvServer>> ServicesToPublish;
	TArray<TSharedPtr<FROSBridgePublisher>> PublisherToPublish;
	TArray<TSharedPtr<FROSBridgeSubscriber>> SubscriberToPublish;


};
