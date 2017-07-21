#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Quaternion.h"

class FROSBridgeMsgGeometrymsgsQuaternionStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsQuaternion quaternion;

public:
    FROSBridgeMsgGeometrymsgsQuaternionStamped()
    {
        Type = "geometry_msgs/QuaternionStamped";
    }

    FROSBridgeMsgGeometrymsgsQuaternionStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsQuaternion quaternion_) :
        header(header_), quaternion(quaternion_)
    {
        Type = "geometry_msgs/QuaternionStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsQuaternionStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsQuaternion GetQuaternion() const
    {
        return quaternion; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetQuaternion(FROSBridgeMsgGeometrymsgsQuaternion quaternion_)
    {
        quaternion = quaternion_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        quaternion = FROSBridgeMsgGeometrymsgsQuaternion::GetFromJson(JsonObject->GetObjectField(TEXT("quaternion")));
    }

    static FROSBridgeMsgGeometrymsgsQuaternionStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsQuaternionStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("QuaternionStamped { header = ") + header.ToString() + 
                     TEXT(", quaternion = ") + quaternion.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("quaternion"), quaternion.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
