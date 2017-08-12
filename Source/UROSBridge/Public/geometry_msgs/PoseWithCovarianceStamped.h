#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/PoseWithCovariance.h"

class FROSBridgeMsgGeometrymsgsPoseWithCovarianceStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsPoseWithCovariance pose;

public:
    FROSBridgeMsgGeometrymsgsPoseWithCovarianceStamped()
    {
        Type = "geometry_msgs/PoseWithCovarianceStamped";
    }

    FROSBridgeMsgGeometrymsgsPoseWithCovarianceStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsPoseWithCovariance pose_) :
        header(header_), pose(pose_)
    {
        Type = "geometry_msgs/PoseWithCovarianceStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsPoseWithCovarianceStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsPoseWithCovariance GetPose() const
    {
        return pose; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetPose(FROSBridgeMsgGeometrymsgsPoseWithCovariance pose_)
    {
        pose = pose_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        pose = FROSBridgeMsgGeometrymsgsPoseWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
    }

    static FROSBridgeMsgGeometrymsgsPoseWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPoseWithCovarianceStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("PoseWithCovarianceStamped { header = ") + header.ToString() + 
                     TEXT(", pose = ") + pose.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("pose"), pose.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
