#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "Json.h"

class FROSBridgeMsg {

protected:
    FString Type;

public:
    FROSBridgeMsg() {

    }

    virtual ~FROSBridgeMsg() {

    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) {

    }

    virtual FString ToString() const
    {
        return TEXT("{}");
    }

    virtual FString ToYamlString() const {
        return TEXT("{}");
    }

    static FString Advertise(const FString& MessageTopic, const FString& MessageType) {
        return TEXT("{\"op\": \"advertise\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"type\": \"") + MessageType +
               TEXT("\"}";)
    }

    static FString UnAdvertise(FString MessageTopic) {
        return TEXT("{\"op\": \"unadvertise\", \"topic\": \"") + MessageTopic + TEXT("\"}");
    }

    static FString Publish(const FString& MessageTopic, const FROSBridgeMsg* Message) {
        return TEXT("{\"op\": \"publish\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"msg\": ") + Message->ToYamlString() +
               TEXT("}";)
    }

    static FString Publish(const FString& MessageTopic, const FString& Message) {
        return TEXT("{\"op\": \"publish\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"msg\": \"") + Message +
               TEXT("\"}";)
    }

    static FString Subscribe(const FString& MessageTopic) {
        return TEXT("{\"op\": \"subscribe\", \"topic\": \"") + MessageTopic + TEXT("\"}");
    }

    static FString Subscribe(const FString& MessageTopic, const FString& MessageType) {
        return TEXT("{\"op\": \"subscribe\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"type\": \"") + MessageType +
               TEXT("\"}";)
    }

    static FString UnSubscribe(const FString& MessageTopic) {
        return TEXT("{\"op\": \"unsubscribe\", \"topic\": \"") + MessageTopic + TEXT("\"}";)
    }

    static FString CallService(const FString& service, const FString& args) {
        if (args == TEXT(""))
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service +  TEXT("\"}");
        else
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service +  TEXT("\", \"args\" : ") + args + TEXT("}");
    }

    static FString CallService(const FString& service) {
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service +  TEXT("\"}");
}
};

