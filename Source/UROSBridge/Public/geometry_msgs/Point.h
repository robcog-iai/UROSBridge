#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsPoint : public FROSBridgeMsg
{
    double x; 
    double y;
    double z;

public:
    FROSBridgeMsgGeometrymsgsPoint()
    {
        Type = "geometry_msgs/Point";
    }

    FROSBridgeMsgGeometrymsgsPoint(double x_, double y_, double z_)
    {
        Type = "geometry_msgs/Point";
        x = x_; y = y_; z = z_; 
    }

    FROSBridgeMsgGeometrymsgsPoint(FVector Vector)
    {
        Type = "geometry_msgs/Point";
        x = Vector.X; y = Vector.Y; z = Vector.Z; 
    }

    ~FROSBridgeMsgGeometrymsgsPoint() override {}

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

    static FROSBridgeMsgGeometrymsgsPoint GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPoint Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Point { x = ") + FString::SanitizeFloat(x) + 
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
