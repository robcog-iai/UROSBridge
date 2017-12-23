#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsQuaternion : public FROSBridgeMsg
{
    double x; 
    double y;
    double z;
    double w; 

public:
    FROSBridgeMsgGeometrymsgsQuaternion()
    {
        Type = "geometry_msgs/Quaternion";
    }

    FROSBridgeMsgGeometrymsgsQuaternion(double x_, double y_, double z_, double w_)
    {
        Type = "geometry_msgs/Quaternion";
        x = x_; y = y_; z = z_;  w = w_; 
    }

    FROSBridgeMsgGeometrymsgsQuaternion(FVector4 Vector)
    {
        Type = "geometry_msgs/Point";
        x = Vector.X; y = Vector.Y; z = Vector.Z; w = Vector.W; 
    }

    ~FROSBridgeMsgGeometrymsgsQuaternion() override {}

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

    double GetW() const
    {
        return w;
    }

    FQuat GetQuat() const 
    {
        return FQuat(x, y, z, w); 
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

    void SetW(double w_)
    {
        w = w_;
    }

    void SetQuat(const FQuat& Quat)
    {
        x = Quat.X; y = Quat.Y; z = Quat.Z; w = Quat.W;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        x = (double)(JsonObject->GetNumberField(TEXT("x"))); 
        y = (double)(JsonObject->GetNumberField(TEXT("y")));
        z = (double)(JsonObject->GetNumberField(TEXT("z")));
        w = (double)(JsonObject->GetNumberField(TEXT("w")));
    }

    static FROSBridgeMsgGeometrymsgsQuaternion GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsQuaternion Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Point { x = ") + FString::SanitizeFloat(x) + 
                     TEXT(", y = ") + FString::SanitizeFloat(y) +
                     TEXT(", z = ") + FString::SanitizeFloat(z) + 
                     TEXT(", w = ") + FString::SanitizeFloat(w) +TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("x"), x);
        Object->SetNumberField(TEXT("y"), y);
        Object->SetNumberField(TEXT("z"), z);
        Object->SetNumberField(TEXT("w"), w);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
