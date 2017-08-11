#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"

class FROSBridgeMsgGeometrymsgsPose : public FROSBridgeMsg
{
    FROSBridgeMsgGeometrymsgsPoint position;
    FROSBridgeMsgGeometrymsgsQuaternion orientation;

public:
    FROSBridgeMsgGeometrymsgsPose()
    {
        Type = "geometry_msgs/Pose";
    }

    FROSBridgeMsgGeometrymsgsPose
    (FROSBridgeMsgGeometrymsgsPoint position_, FROSBridgeMsgGeometrymsgsQuaternion orientation_) :
        position(position_), orientation(orientation_)
    {
        Type = "geometry_msgs/Pose";
    }
    
    ~FROSBridgeMsgGeometrymsgsPose() override {}

    FROSBridgeMsgGeometrymsgsPoint GetPosition() const
    {
        return position; 
    }

    FROSBridgeMsgGeometrymsgsQuaternion GetOrientation() const
    {
        return orientation; 
    }

    void SetPosition(FROSBridgeMsgGeometrymsgsPoint position_)
    {
        position = position_; 
    }

    void SetOrientation(FROSBridgeMsgGeometrymsgsQuaternion orientation_)
    {
        orientation = orientation_; 
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        position = FROSBridgeMsgGeometrymsgsPoint::GetFromJson(JsonObject->GetObjectField(TEXT("position")));
        orientation = FROSBridgeMsgGeometrymsgsQuaternion::GetFromJson(JsonObject->GetObjectField(TEXT("orientation")));
    }

    static FROSBridgeMsgGeometrymsgsPose GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPose Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Pose { position = ") + position.ToString() + 
                     TEXT(", orientation = ") + orientation.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("position"), position.ToJsonObject());
        Object->SetObjectField(TEXT("orientation"), orientation.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
