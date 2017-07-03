#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "Json.h"

#include "ROSBridgeMsg.h"

class UROSBridgeSubscriber : UObject {
    FString Type;
    FString Topic;

public:

    UROSBridgeSubscriber(FString Type_, FString Topic_):
        Type(Type_), Topic(Topic_)
    {

    }

    virtual FString GetMessageType() const {
        return Type;
    }

    virtual FString GetMessageTopic() const {
        return Topic;
    }

    virtual TSharedPtr<FROSBridgeMsg> ParseMessage(const FJsonObject* JsonObject) {
        return NULL;
    }

    virtual void CallBack(const FROSBridgeMsg* msg) {
        return;
    }
};
