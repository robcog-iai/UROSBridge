#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "UObject.h"
#include "ROSBridgeMsg.h"

class UROSBridgePublisher : UObject {
    FString Type;
    FString Topic;

public:

    UROSBridgePublisher(FString Type_, FString Topic_):
        Type(Type_), Topic(Topic_)
    {

    }

    virtual FString GetMessageType() const {
        return Type;
    }

    virtual FString GetMessageTopic() const {
        return Topic;
    }

    virtual FString ToYamlString() const {
        return TEXT("");
    }
};
