// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "Core.h"
#include "Json.h"

#include "ROSTime.h"

class UROSBRIDGE_API FROSBridgeMsg 
{

protected:
    FString MsgType;

public:
    FROSBridgeMsg() {}
	
    virtual ~FROSBridgeMsg() {}

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) { }

	virtual TSharedPtr<FJsonObject> ToJsonObject() const 
	{
		return MakeShareable<FJsonObject>(new FJsonObject());
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

	static FORCEINLINE FString Advertise(const FString& InMessageTopic, const FString& InMessageType)
	{
        return TEXT("{\"op\": \"advertise\", \"topic\": \"") + InMessageTopic +
               TEXT("\", \"type\": \"") + InMessageType +
               TEXT("\"}";)
    }

    static FORCEINLINE FString UnAdvertise(FString InMessageTopic)
	{
        return TEXT("{\"op\": \"unadvertise\", \"topic\": \"") + InMessageTopic + TEXT("\"}");
    }

    static FORCEINLINE FString Publish(const FString& InMessageTopic, TSharedPtr<FROSBridgeMsg> Message)
	{
        return TEXT("{\"op\": \"publish\", \"topic\": \"") + InMessageTopic +
               TEXT("\", \"msg\": ") + Message->ToYamlString() +
               TEXT("}";)
    }

    static FORCEINLINE FString Publish(const FString& InMessageTopic, const FString& Message)
	{
        return TEXT("{\"op\": \"publish\", \"topic\": \"") + InMessageTopic +
               TEXT("\", \"msg\": \"") + Message +
               TEXT("\"}";)
    }

    static FORCEINLINE FString Subscribe(const FString& InMessageTopic)
	{
        return TEXT("{\"op\": \"subscribe\", \"topic\": \"") + InMessageTopic + TEXT("\"}");
    }

    static FORCEINLINE FString Subscribe(const FString& InMessageTopic, const FString& InMessageType)
	{
        return TEXT("{\"op\": \"subscribe\", \"topic\": \"") + InMessageTopic +
               TEXT("\", \"type\": \"") + InMessageType +
               TEXT("\"}";)
    }

    static FORCEINLINE FString UnSubscribe(const FString& InMessageTopic)
	{
        return TEXT("{\"op\": \"unsubscribe\", \"topic\": \"") + InMessageTopic + TEXT("\"}";)
    }

    static FORCEINLINE FString CallService(const FString& InService, const FString& InArgs)
	{
        if (InArgs == TEXT(""))
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService +  TEXT("\"}");
        else
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService +  TEXT("\", \"args\" : ") + InArgs + TEXT("}");
    }

    static FORCEINLINE FString CallService(const FString& InService)
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService +  TEXT("\"}");
	}
};

