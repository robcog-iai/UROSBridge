// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "ROSBridgeMsg.h"

class UROSBRIDGE_API FROSBridgePublisher 
{
    FString Type;
    FString Topic;

public:

    FROSBridgePublisher(FString Type_, FString Topic_):
        Type(Type_), Topic(Topic_)
    {
    }

    virtual ~FROSBridgePublisher() {}

    virtual FString GetMessageType() const 
	{
        return Type;
    }

    virtual FString GetMessageTopic() const 
	{
        return Topic;
    }

    virtual FString ToYamlString() const 
	{
        return TEXT("");
    }
};
