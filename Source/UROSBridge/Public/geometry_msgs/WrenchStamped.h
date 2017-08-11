#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Wrench.h"

class FROSBridgeMsgGeometrymsgsWrenchStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsWrench wrench;

public:
    FROSBridgeMsgGeometrymsgsWrenchStamped()
    {
        Type = "geometry_msgs/WrenchStamped";
    }

    FROSBridgeMsgGeometrymsgsWrenchStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsWrench wrench_) :
        header(header_), wrench(wrench_)
    {
        Type = "geometry_msgs/WrenchStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsWrenchStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsWrench GetWrench() const
    {
        return wrench; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetWrench(FROSBridgeMsgGeometrymsgsWrench wrench_)
    {
        wrench = wrench_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        wrench = FROSBridgeMsgGeometrymsgsWrench::GetFromJson(JsonObject->GetObjectField(TEXT("wrench")));
    }

    static FROSBridgeMsgGeometrymsgsWrenchStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsWrenchStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("WrenchStamped { header = ") + header.ToString() + 
                     TEXT(", wrench = ") + wrench.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("wrench"), wrench.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
