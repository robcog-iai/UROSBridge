#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsVector3 : public FROSBridgeMsg
{
    double x; 
    double y;
    double z;

public:
    FROSBridgeMsgGeometrymsgsVector3()
    {
        Type = "geometry_msgs/Vector3";
    }

    FROSBridgeMsgGeometrymsgsVector3(double x_, double y_, double z_)
    {
        Type = "geometry_msgs/Vector3";
        x = x_; y = y_; z = z_; 
    }

    FROSBridgeMsgGeometrymsgsVector3(FVector Vector)
    {
        Type = "geometry_msgs/Vector3";
        x = Vector.X; y = Vector.Y; z = Vector.Z; 
    }

    ~FROSBridgeMsgGeometrymsgsVector3() override {}

    double GetX() const 
    {
        return x;
    }

    double GetY() const
    {
        return y;
    }

    double GetZ() const
    {
        return z;
    }

    FVector GetVector() const 
    {
        return FVector(x, y, z); 
    }

    void SetX(double x_)
    {
        x = x_; 
    }

    void SetY(double y_)
    {
        y = y_;
    }

    void SetZ(double z_)
    {
        z = z_;
    }

    void SetVector(const FVector & Vector)
    {
        x = Vector.X; y = Vector.Y; z = Vector.Z;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        x = (double)(JsonObject->GetNumberField(TEXT("x"))); 
        y = (double)(JsonObject->GetNumberField(TEXT("y")));
        z = (double)(JsonObject->GetNumberField(TEXT("z")));
    }

    static FROSBridgeMsgGeometrymsgsVector3 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsVector3 Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Vector3 { x = ") + FString::SanitizeFloat(x) + 
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
