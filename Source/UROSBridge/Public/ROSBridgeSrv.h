// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "Core.h"
#include "Json.h"

class UROSBRIDGE_API FROSBridgeSrv 
{
public:
    class SrvRequest; 
    class SrvResponse; 

protected:
    FString SrvType;
    TSharedPtr<SrvRequest> Request;
    TSharedPtr<SrvResponse> Response;

public:

    class Message
    {
    public:
        Message() {}
        virtual ~Message() {}

        // Need Implementation
        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) = 0; 

        // Need Implementation 
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
    };

    class SrvRequest : public Message 
	{
    };

    class SrvResponse : public Message 
	{
    };

    FROSBridgeSrv() 
	{
    }

    virtual ~FROSBridgeSrv() 
	{
    }

	static FORCEINLINE FString AdvertiseService(const FString& InService, const FString& InType)
	{
        return TEXT("{\"op\": \"advertise_service\", \"service\": \"") + InService + TEXT("\", \"type\": \"") + InType + TEXT("\"}");
    }

    static FORCEINLINE FString UnadvertiseService(const FString& InService)
	{
        return TEXT("{\"op\": \"unadvertise_service\", \"service\": \"") + InService + TEXT("\"}");
    }

    static FORCEINLINE FString ServiceResponse(const FString& InService, const FString& InId, TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse)
	{
        return TEXT("{\"op\": \"service_response\", \"service\": \"") + InService + TEXT("\", ") +
            TEXT("\"values\" : ") + InResponse->ToYamlString() + TEXT(", ") +
            TEXT("\"id\" : \"") + InId + TEXT("\" }");
    }

    static FORCEINLINE FString CallService(const FString& InService, TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest)
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService + TEXT("\", \"args\" : ") + InRequest->ToYamlString() + TEXT("}");
    }

    static FORCEINLINE FString CallService(const FString& InService, TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest, const FString& InId)
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService + TEXT("\", ") +
                TEXT("\"args\" : ") + InRequest->ToYamlString() + TEXT(", ") +
                TEXT("\"id\" : \"") + InId + TEXT("\" }");
    }

    static FORCEINLINE FString CallService(const FString& InService, const FString& InArgs)
	{
        if (InArgs == TEXT(""))
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService + TEXT("\"}");
        else
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService + TEXT("\", \"args\" : ") + InArgs + TEXT("}");
    }

    static FORCEINLINE FString CallService(const FString& InService)
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + InService + TEXT("\"}");
    }
};

