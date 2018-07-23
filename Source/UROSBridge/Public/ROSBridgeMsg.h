// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "Core.h"
#include "Json.h"
#include "FBson.h"
#include "UROSBridge.h"
#include "ROSTime.h"

class UROSBRIDGE_API FROSBridgeMsg 
{

protected:
	FString MsgType;

public:
	FROSBridgeMsg() {}
	
	virtual ~FROSBridgeMsg() {}

	virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) { 
		UE_LOG(LogROS, Warning, TEXT("Message Object not changed. Did you forget to overwrite FromJson somewhere?")); 
	}

	virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) {
		UE_LOG(LogROS, Warning, TEXT("Message Object not changed. Did you forget to overwrite FromBson somewhere?"));
	}

	virtual TSharedPtr<FJsonObject> ToJsonObject() const 
	{
		UE_LOG(LogROS, Warning, TEXT("Message Object created empty. Did you forget to overwrite ToJsonObject() somewhere?"));
		return MakeShareable<FJsonObject>(new FJsonObject());
	}

	virtual TSharedPtr<FBsonObject> ToBsonObject() const 
	{
		UE_LOG(LogROS, Warning, TEXT("Service Object created empty. Did you forget to overwrite ToBsonObject() somewhere?"));
		return MakeShareable(new FBsonObject());
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

