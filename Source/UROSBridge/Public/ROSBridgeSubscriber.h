// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Json.h"
#include "ROSBridgeMsg.h"

class UROSBRIDGE_API FROSBridgeSubscriber 
{
    FString Type;
    FString Topic;

public:

    FROSBridgeSubscriber(FString Type_, FString Topic_):
        Type(Type_), Topic(Topic_)
    {
    }

    virtual ~FROSBridgeSubscriber() 
	{
    }

    virtual FString GetMessageType() const 
	{
        return Type;
    }

    virtual FString GetMessageTopic() const 
	{
        return Topic;
    }

    virtual TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const = 0;

    virtual void CallBack(TSharedPtr<FROSBridgeMsg> msg) const = 0;
};
