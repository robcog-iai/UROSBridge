// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Json.h"
#include "FBson.h"
#include "ROSBridgeMsg.h"

class UROSBRIDGE_API FROSBridgeSubscriber 
{
protected:
	FString Topic;
	FString Type;

public:

	FROSBridgeSubscriber(FString InTopic, FString InType):
		Topic(InTopic), Type(InType)
	{
	}

	virtual ~FROSBridgeSubscriber() 
	{
	}

	virtual FString GetType() const 
	{
		return Type;
	}

	virtual FString GetTopic() const 
	{
		return Topic;
	}

	virtual TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const {
		UE_LOG(LogROS, Warning, TEXT("ParseMessage() was not overwritten for Json based data transfer."));
	}

	virtual TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FBsonObject> BsonObject) const {
		UE_LOG(LogROS, Warning, TEXT("ParseMessage() was not overwritten for Bson based data transfer."));
	}

	virtual void Callback(TSharedPtr<FROSBridgeMsg> Msg) = 0;
};
