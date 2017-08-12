#pragma once

#include "ROSBridgeSrv.h"

class UROSBRIDGE_API FROSBridgeSrvStdsrvsSetBool : public FROSBridgeSrv {

protected:
    FString Type;

public:
    FROSBridgeSrvStdsrvsSetBool()
    {
        Type = TEXT("srd_srvs/SetBool");
    }

    class Request : public SrvRequest {
    private:
        uint8 data;

    public:
        Request() { }
        Request(uint8 data_) : data(data_) {}
        uint8 GetData() const { return data; }
        void SetData(uint8 data_) { data = data_; }

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            data = JsonObject->GetIntegerField("data");
        }

        static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Request req; req.FromJson(JsonObject); 
            return req;
        }

        virtual FString ToString() const override
        {
            return TEXT("SetBool::Request { data = " ) + FString::FromInt(data) + TEXT(" } ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            Object->SetNumberField(TEXT("data"), data); 
            return Object;
        }
    };

    class Response : public SrvResponse {
    private:
        uint8 success;
        FString message; 

    public:
        Response() {}
        Response(uint8 success_, FString message_) : success(success_), message(message_) {}
        uint8 GetSuccess() const { return success; }
        FString GetMessage() const { return message; }
        void SetSuccess(uint8 success_) { success = success_; }
        void SetMessage(FString message_) { message = message_; }

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            success = JsonObject->GetIntegerField("success");
            message = JsonObject->GetStringField("message");
        }

        static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Response rep; rep.FromJson(JsonObject); 
            return rep; 
        }

        virtual FString ToString() const override
        {
            return TEXT("SetBool::Response { success = ") + FString::FromInt(success) + TEXT(", ") + 
                                      TEXT(" message = \"") + message + TEXT("\" } ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            Object->SetNumberField("success", success); 
            Object->SetStringField("message", message);
            return Object;
        }
    };

};

