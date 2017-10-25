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
    FString Type;
    FString Name; 
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

    static FString AdvertiseService(const FString& service, const FString& type) 
	{
        return TEXT("{\"op\": \"advertise_service\", \"service\": \"") + service + TEXT("\", \"type\": \"") + type + TEXT("\"}");
    }

    static FString UnadvertiseService(const FString& service) 
	{
        return TEXT("{\"op\": \"unadvertise_service\", \"service\": \"") + service + TEXT("\"}");
    }

    static FString ServiceResponse(const FString& service, const FString& ID, TSharedPtr<FROSBridgeSrv::SrvResponse> Resp) 
	{
        return TEXT("{\"op\": \"service_response\", \"service\": \"") + service + TEXT("\", ") +
            TEXT("\"values\" : ") + Resp->ToYamlString() + TEXT(", ") +
            TEXT("\"id\" : \"") + ID + TEXT("\" }");
    }

    static FString CallService(const FString& service, TSharedPtr<FROSBridgeSrv::SrvRequest> Req) 
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\", \"args\" : ") + Req->ToYamlString() + TEXT("}");
    }

    static FString CallService(const FString& service, TSharedPtr<FROSBridgeSrv::SrvRequest> Req, const FString& ID) 
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\", ") +
                TEXT("\"args\" : ") + Req->ToYamlString() + TEXT(", ") +
                TEXT("\"id\" : \"") + ID + TEXT("\" }");
    }

    static FString CallService(const FString& service, const FString& args) 
	{
        if (args == TEXT(""))
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\"}");
        else
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\", \"args\" : ") + args + TEXT("}");
    }

    static FString CallService(const FString& service) 
	{
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\"}");
    }
};

