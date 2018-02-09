// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "ROSBridgeMsg.h"

class UROSBRIDGE_API FROSBridgePublisher 
{
protected:
    FString Topic;
    FString Type;

public:

    FROSBridgePublisher(FString InTopic, FString InType):
		Topic(InTopic), Type(InType)
    {
    }

    virtual ~FROSBridgePublisher() {}

    virtual FString GetType() const 
	{
        return Type;
    }

    virtual FString GetTopic() const 
	{
        return Topic;
    }

    virtual FString ToYamlString() const 
	{
        return TEXT("");
    }
};
