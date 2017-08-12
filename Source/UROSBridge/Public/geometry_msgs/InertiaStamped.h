#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Inertia.h"

class FROSBridgeMsgGeometrymsgsInertiaStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsInertia inertia;

public:
    FROSBridgeMsgGeometrymsgsInertiaStamped()
    {
        Type = "geometry_msgs/InertiaStamped";
    }

    FROSBridgeMsgGeometrymsgsInertiaStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsInertia inertia_) :
        header(header_), inertia(inertia_)
    {
        Type = "geometry_msgs/InertiaStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsInertiaStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsInertia GetInertia() const
    {
        return inertia; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetInertia(FROSBridgeMsgGeometrymsgsInertia inertia_)
    {
        inertia = inertia_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        inertia = FROSBridgeMsgGeometrymsgsInertia::GetFromJson(JsonObject->GetObjectField(TEXT("inertia")));
    }

    static FROSBridgeMsgGeometrymsgsInertiaStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsInertiaStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("InertiaStamped { header = ") + header.ToString() + 
                     TEXT(", inertia = ") + inertia.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("inertia"), inertia.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
