#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsPoint32 : public FROSBridgeMsg
{
    float x; 
    float y;
    float z;

public:
    FROSBridgeMsgGeometrymsgsPoint32()
    {
        Type = "geometry_msgs/Point32";
    }

    FROSBridgeMsgGeometrymsgsPoint32(float x_, float y_, float z_)
    {
        Type = "geometry_msgs/Point32";
        x = x_; y = y_; z = z_; 
    }

    FROSBridgeMsgGeometrymsgsPoint32(FVector Vector)
    {
        Type = "geometry_msgs/Point32";
        x = Vector.X; y = Vector.Y; z = Vector.Z; 
    }

    ~FROSBridgeMsgGeometrymsgsPoint32() override {}

    float GetX() const 
    {
        return x;
    }

    float GetY() const
    {
        return y;
    }

    float GetZ() const
    {
        return z;
    }

    FVector GetVector() const 
    {
        return FVector(x, y, z); 
    }

    void SetX(float x_)
    {
        x = x_; 
    }

    void SetY(float y_)
    {
        y = y_;
    }

    void SetZ(float z_)
    {
        z = z_;
    }

    void SetVector(const FVector & Vector)
    {
        x = Vector.X; y = Vector.Y; z = Vector.Z;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        x = (float)(JsonObject->GetNumberField(TEXT("x"))); 
        y = (float)(JsonObject->GetNumberField(TEXT("y")));
        z = (float)(JsonObject->GetNumberField(TEXT("z")));
    }

    static FROSBridgeMsgGeometrymsgsPoint32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPoint32 Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Point32 { x = ") + FString::SanitizeFloat(x) + 
                       TEXT(", y = ") + FString::SanitizeFloat(y) +
                       TEXT(", z = ") + FString::SanitizeFloat(z) + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("x"), x);
        Object->SetNumberField(TEXT("y"), y);
        Object->SetNumberField(TEXT("z"), z);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
