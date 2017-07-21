#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsPose2D : public FROSBridgeMsg
{
    double x; 
    double y;
    double theta;

public:
    FROSBridgeMsgGeometrymsgsPose2D()
    {
        Type = "geometry_msgs/Pose2D";
    }

    FROSBridgeMsgGeometrymsgsPose2D(double x_, double y_, double theta_)
    {
        Type = "geometry_msgs/Pose2D";
        x = x_; y = y_; theta = theta_; 
    }

    FROSBridgeMsgGeometrymsgsPose2D(FVector Vector)
    {
        Type = "geometry_msgs/Pose2D";
        x = Vector.X; y = Vector.Y; theta = Vector.Z; 
    }

    ~FROSBridgeMsgGeometrymsgsPose2D() override {}

    double GetX() const 
    {
        return x;
    }

    double GetY() const
    {
        return y;
    }

    double GetTheta() const
    {
        return theta;
    }

    FVector GetVector() const 
    {
        return FVector(x, y, theta); 
    }

    void SetX(double x_)
    {
        x = x_; 
    }

    void SetY(double y_)
    {
        y = y_;
    }

    void SetTheta(double theta_)
    {
        theta = theta_;
    }

    void SetVector(const FVector & Vector)
    {
        x = Vector.X; y = Vector.Y; theta = Vector.Z;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        x = (double)(JsonObject->GetNumberField(TEXT("x"))); 
        y = (double)(JsonObject->GetNumberField(TEXT("y")));
        theta = (double)(JsonObject->GetNumberField(TEXT("theta")));
    }

    static FROSBridgeMsgGeometrymsgsPose2D GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPose2D Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Pose2D { x = ") + FString::SanitizeFloat(x) + 
                     TEXT(", y = ") + FString::SanitizeFloat(y) +
                     TEXT(", theta = ") + FString::SanitizeFloat(theta) + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("x"), x);
        Object->SetNumberField(TEXT("y"), y);
        Object->SetNumberField(TEXT("theta"), theta);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
