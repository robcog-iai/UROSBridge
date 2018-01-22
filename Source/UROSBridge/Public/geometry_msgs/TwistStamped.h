#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Twist.h"

class FROSBridgeMsgGeometrymsgsTwistStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsTwist twist;

public:
    FROSBridgeMsgGeometrymsgsTwistStamped()
    {
        Type = "geometry_msgs/TwistStamped";
    }

    FROSBridgeMsgGeometrymsgsTwistStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsTwist twist_) :
        header(header_), twist(twist_)
    {
        Type = "geometry_msgs/TwistStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsTwistStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsTwist GetTwist() const
    {
        return twist; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetTwist(FROSBridgeMsgGeometrymsgsTwist twist_)
    {
        twist = twist_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        twist = FROSBridgeMsgGeometrymsgsTwist::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));
    }

    static FROSBridgeMsgGeometrymsgsTwistStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsTwistStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("TwistStamped { header = ") + header.ToString() + 
                     TEXT(", twist = ") + twist.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("twist"), twist.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace geometry_msgs
{
} // namespace geometry_msgs