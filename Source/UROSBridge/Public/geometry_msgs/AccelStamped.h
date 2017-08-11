#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Accel.h"

class FROSBridgeMsgGeometrymsgsAccelStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsAccel accel;

public:
    FROSBridgeMsgGeometrymsgsAccelStamped()
    {
        Type = "geometry_msgs/AccelStamped";
    }

    FROSBridgeMsgGeometrymsgsAccelStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsAccel accel_) :
        header(header_), accel(accel_)
    {
        Type = "geometry_msgs/AccelStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsAccelStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsAccel GetAccel() const
    {
        return accel; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetAccel(FROSBridgeMsgGeometrymsgsAccel accel_)
    {
        accel = accel_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        accel = FROSBridgeMsgGeometrymsgsAccel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));
    }

    static FROSBridgeMsgGeometrymsgsAccelStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsAccelStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("AccelStamped { header = ") + header.ToString() + 
                     TEXT(", accel = ") + accel.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("accel"), accel.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
