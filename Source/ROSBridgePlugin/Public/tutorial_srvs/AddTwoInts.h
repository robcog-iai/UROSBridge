#pragma once

#include "ROSBridgeSrv.h"

class ROSBRIDGEPLUGIN_API FROSBridgeSrvRospytutorialsAddTwoInts : public FROSBridgeSrv {

protected:
    FString Type;

public:
    FROSBridgeSrvRospytutorialsAddTwoInts()
    {
        Type = TEXT("rospy_tutorials/AddTwoInts");
    }

    class Request : public SrvRequest {
    private:
        int64 a;
        int64 b; 

    public:
        Request() { }
        Request(int64 a_, int64 b_) : a(a_), b(b_) {}
        int64 GetA() const { return a; }
        void SetA(int64 a_) { a = a_; }
        int64 GetB() const { return b; }
        void SetB(int64 b_) { b = b_; }

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            a = JsonObject->GetNumberField("a");
            b = JsonObject->GetNumberField("b");
        }

        static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Request req; req.FromJson(JsonObject);
            return req;
        }

        virtual FString ToString() const override
        {
            return TEXT("AddTwoInts::Request { a = ") + FString::FromInt(a) +
                                       TEXT(", b = ") + FString::FromInt(b) + TEXT("} ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            Object->SetNumberField(TEXT("a"), a);
            Object->SetNumberField(TEXT("b"), b);
            return Object;
        }
    };

    class Response : public SrvResponse {
    private:
        int64 sum;

    public:
        Response() {}
        Response(int64 sum_) : sum(sum_) {}
        int64 GetSum() const { return sum; }
        void SetSum(int64 sum_) { sum = sum_; }

        virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
            sum = JsonObject->GetNumberField("sum");
        }

        static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
        {
            Response rep; rep.FromJson(JsonObject);
            return rep;
        }

        virtual FString ToString() const override
        {
            return TEXT("AddTwoInts::Response { sum = ") + FString::SanitizeFloat(sum) + TEXT(" } ");
        }

        virtual TSharedPtr<FJsonObject> ToJsonObject() const {
            TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
            Object->SetNumberField("sum", sum);
            return Object;
        }
    };

};

