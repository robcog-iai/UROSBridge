#pragma once

#include "ROSBridgeSubscriber.h"
#include "std_msgs/String.h"
#include "Core.h"

class FROSStringSubScriber : public FROSBridgeSubscriber {

public:
    FROSStringSubScriber(FString Topic_) :
        FROSBridgeSubscriber(TEXT("std_msgs/String"), Topic_)
    {

    }

    ~FROSStringSubScriber() override {};

    TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override
    {
        TSharedPtr<FROSBridgeMsgStdmsgsString> StringMessage = 
            MakeShareable<FROSBridgeMsgStdmsgsString>(new FROSBridgeMsgStdmsgsString());
        StringMessage->FromJson(JsonObject);
        UE_LOG(LogTemp, Log, TEXT("Data in String Message: %s"), *StringMessage->GetData());

        return StaticCastSharedPtr<FROSBridgeMsg>(StringMessage);
    }

    void CallBack(TSharedPtr<FROSBridgeMsg> msg) const override
    {
        TSharedPtr<FROSBridgeMsgStdmsgsString> StringMessage = StaticCastSharedPtr<FROSBridgeMsgStdmsgsString>(msg);
        // do something
        UE_LOG(LogTemp, Log, TEXT("Message received! Content: %s"), *StringMessage->GetData());

        return;
    }

};
