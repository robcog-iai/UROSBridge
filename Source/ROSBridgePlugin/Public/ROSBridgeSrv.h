#pragma once

#include "Core.h"
#include "LogMacros.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "Json.h"

#include "ROSTime.h"

class ROSBRIDGEPLUGIN_API FROSBridgeSrv {
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
        ~Message() {}

        // Need Implementation
        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) = 0; 

        // Need Implementation 
        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> NewObject = MakeShareable<FJsonObject>(new FJsonObject());
            return NewObject;
        }

        virtual FString ToString() const
        {
            return TEXT("{}");
        }

        virtual FString ToYamlString() const {
            FString OutputString;
            TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
            FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
            return OutputString;
        }
    };

    class SrvRequest : public Message {

    };

    class SrvResponse : public Message {

    };

    FROSBridgeSrv() {

    }

    virtual ~FROSBridgeSrv() {

    }

    static FString CallService(const FString& service, const FROSBridgeSrv::SrvRequest* Req) {
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\", \"args\" : ") + Req->ToYamlString() + TEXT("}");
    }

    static FString CallService(const FString& service, const FROSBridgeSrv::SrvRequest* Req, FString ID) {
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\", ") +
                TEXT("\"args\" : ") + Req->ToYamlString() + TEXT("\", ") +
                TEXT("\"id\" : ") + ID + TEXT("\" }");
    }

    static FString CallService(const FString& service, const FString& args) {
        if (args == TEXT(""))
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\"}");
        else
            return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\", \"args\" : ") + args + TEXT("}");
    }

    static FString CallService(const FString& service) {
        return TEXT("{\"op\": \"call_service\", \"service\": \"") + service + TEXT("\"}");
    }
};

