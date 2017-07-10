#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "Json.h"
#include "ROSBridgeMsg.h"

class FROSBridgeSubscriber {
    FString Type;
    FString Topic;

public:

    FROSBridgeSubscriber(FString Type_, FString Topic_):
        Type(Type_), Topic(Topic_)
    {

    }

    virtual ~FROSBridgeSubscriber() {

    }

    virtual FString GetMessageType() const {
        return Type;
    }

    virtual FString GetMessageTopic() const {
        return Topic;
    }

    virtual FROSBridgeMsg* ParseMessage(TSharedPtr<FJsonObject> JsonObject) {
        return NULL;
    }

    virtual void CallBack(FROSBridgeMsg* msg) {
        return;
    }
};
