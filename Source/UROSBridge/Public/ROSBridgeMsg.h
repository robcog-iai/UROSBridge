// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "Core.h"
#include "Json.h"

#include "ROSTime.h"

class UROSBRIDGE_API FROSBridgeMsg 
{

protected:
    FString Type;

public:
    FROSBridgeMsg() {}
	
    virtual ~FROSBridgeMsg() {}

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) {}

	virtual TSharedPtr<FJsonObject> ToJsonObject() const 
	{
		TSharedPtr<FJsonObject> NewObject = MakeShareable<FJsonObject>(new FJsonObject());
		return NewObject; 
	}

    virtual FString ToString() const
    {
        return TEXT("{}");
    }

    virtual FString ToYamlString() const 
	{
		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
		return OutputString;
    }

	static FORCEINLINE FString Advertise(const FString& MessageTopic, const FString& MessageType)
	{
        return TEXT("{\"op\": \"advertise\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"type\": \"") + MessageType +
               TEXT("\"}";)
    }

    static FORCEINLINE FString UnAdvertise(FString MessageTopic)
	{
        return TEXT("{\"op\": \"unadvertise\", \"topic\": \"") + MessageTopic + TEXT("\"}");
    }

    static FORCEINLINE FString Publish(const FString& MessageTopic, TSharedPtr<FROSBridgeMsg> Message)
	{
        return TEXT("{\"op\": \"publish\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"msg\": ") + Message->ToYamlString() +
               TEXT("}";)
    }

    static FORCEINLINE FString Publish(const FString& MessageTopic, const FString& Message)
	{
        return TEXT("{\"op\": \"publish\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"msg\": \"") + Message +
               TEXT("\"}";)
    }

    static FORCEINLINE FString Subscribe(const FString& MessageTopic)
	{
        return TEXT("{\"op\": \"subscribe\", \"topic\": \"") + MessageTopic + TEXT("\"}");
    }

    static FORCEINLINE FString Subscribe(const FString& MessageTopic, const FString& MessageType)
	{
        return TEXT("{\"op\": \"subscribe\", \"topic\": \"") + MessageTopic +
               TEXT("\", \"type\": \"") + MessageType +
               TEXT("\"}";)
    }

    static FORCEINLINE FString UnSubscribe(const FString& MessageTopic)
	{
        return TEXT("{\"op\": \"unsubscribe\", \"topic\": \"") + MessageTopic + TEXT("\"}";)
    }

    static FORCEINLINE FString CallService(const FString& service, const FString& args)
	{
        if (args == TEXT(""))
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service +  TEXT("\"}");
        else
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service +  TEXT("\", \"args\" : ") + args + TEXT("}");
    }

    static FORCEINLINE FString CallService(const FString& service)
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service +  TEXT("\"}");
	}
};

