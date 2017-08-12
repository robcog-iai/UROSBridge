#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"

class FROSBridgeMsgGeometrymsgsWrench : public FROSBridgeMsg
{
    FROSBridgeMsgGeometrymsgsVector3 force;
    FROSBridgeMsgGeometrymsgsVector3 torque;

public:
    FROSBridgeMsgGeometrymsgsWrench()
    {
        Type = "geometry_msgs/Wrench";
    }

    FROSBridgeMsgGeometrymsgsWrench
    (FROSBridgeMsgGeometrymsgsVector3 force_, FROSBridgeMsgGeometrymsgsVector3 torque_) :
        force(force_), torque(torque_)
    {
        Type = "geometry_msgs/Wrench";
    }
    
    ~FROSBridgeMsgGeometrymsgsWrench() override {}

    FROSBridgeMsgGeometrymsgsVector3 GetForce() const
    {
        return force; 
    }

    FROSBridgeMsgGeometrymsgsVector3 GetTorque() const
    {
        return torque; 
    }

    void SetForce(FROSBridgeMsgGeometrymsgsVector3 force_)
    {
        force = force_; 
    }

    void SetTorque(FROSBridgeMsgGeometrymsgsVector3 torque_)
    {
        torque = torque_; 
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        force = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("force")));
        torque = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("torque")));
    }

    static FROSBridgeMsgGeometrymsgsWrench GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsWrench Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Wrench { force = ") + force.ToString() + 
                     TEXT(", torque = ") + torque.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("force"), force.ToJsonObject());
        Object->SetObjectField(TEXT("torque"), torque.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
