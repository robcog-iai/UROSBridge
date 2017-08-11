#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"

class FROSBridgeMsgGeometrymsgsTwist : public FROSBridgeMsg
{
    FROSBridgeMsgGeometrymsgsVector3 linear;
    FROSBridgeMsgGeometrymsgsVector3 angular;

public:
    FROSBridgeMsgGeometrymsgsTwist()
    {
        Type = "geometry_msgs/Twist";
    }

    FROSBridgeMsgGeometrymsgsTwist
    (FROSBridgeMsgGeometrymsgsVector3 linear_, FROSBridgeMsgGeometrymsgsVector3 angular_) :
        linear(linear_), angular(angular_)
    {
        Type = "geometry_msgs/Twist";
    }
    
    ~FROSBridgeMsgGeometrymsgsTwist() override {}

    FROSBridgeMsgGeometrymsgsVector3 GetLinear() const
    {
        return linear; 
    }

    FROSBridgeMsgGeometrymsgsVector3 GetAngular() const
    {
        return angular; 
    }

    void SetLinear(FROSBridgeMsgGeometrymsgsVector3 linear_)
    {
        linear = linear_; 
    }

    void SetAngular(FROSBridgeMsgGeometrymsgsVector3 angular_)
    {
        angular = angular_; 
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        linear = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("linear")));
        angular = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("angular")));
    }

    static FROSBridgeMsgGeometrymsgsTwist GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsTwist Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Twist { linear = ") + linear.ToString() + 
                     TEXT(", angular = ") + angular.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("linear"), linear.ToJsonObject());
        Object->SetObjectField(TEXT("angular"), angular.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
