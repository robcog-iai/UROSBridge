#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"

class FROSBridgeMsgGeometrymsgsTransform : public FROSBridgeMsg
{
    FROSBridgeMsgGeometrymsgsVector3 translation;
    FROSBridgeMsgGeometrymsgsQuaternion rotation;

public:
    FROSBridgeMsgGeometrymsgsTransform()
    {
        Type = "geometry_msgs/Transform";
    }

    FROSBridgeMsgGeometrymsgsTransform
    (FROSBridgeMsgGeometrymsgsVector3 translation_, FROSBridgeMsgGeometrymsgsQuaternion rotation_) :
        translation(translation_), rotation(rotation_)
    {
        Type = "geometry_msgs/Transform";
    }
    
    ~FROSBridgeMsgGeometrymsgsTransform() override {}

    FROSBridgeMsgGeometrymsgsVector3 GetTranslation() const
    {
        return translation; 
    }

    FROSBridgeMsgGeometrymsgsQuaternion GetRotation() const
    {
        return rotation; 
    }

    void SetTranslation(FROSBridgeMsgGeometrymsgsVector3 translation_)
    {
        translation = translation_; 
    }

    void SetRotation(FROSBridgeMsgGeometrymsgsQuaternion rotation_)
    {
        rotation = rotation_; 
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        translation = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("translation")));
        rotation = FROSBridgeMsgGeometrymsgsQuaternion::GetFromJson(JsonObject->GetObjectField(TEXT("rotation")));
    }

    static FROSBridgeMsgGeometrymsgsTransform GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsTransform Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Transform { translation = ") + translation.ToString() + 
                     TEXT(", rotation = ") + rotation.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("translation"), translation.ToJsonObject());
        Object->SetObjectField(TEXT("rotation"), rotation.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
