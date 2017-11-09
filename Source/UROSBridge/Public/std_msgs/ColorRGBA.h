#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsColorRGBA : public FROSBridgeMsg
{
    float r;
    float g;
    float b;
    float a;

public:
    FROSBridgeMsgStdmsgsColorRGBA()
    {
        Type = "std_msgs/ColorRGBA";
    }

    FROSBridgeMsgStdmsgsColorRGBA(float r_, float g_, float b_, float a_)
    {
        Type = "std_msgs/ColorRGBA";
        r = r_; g = g_; b = b_; a = a_;
    }

    ~FROSBridgeMsgStdmsgsColorRGBA() override {}


    FVector GetColor() const
    {
        return FVector4(r, g, b, a);
    }

    void SetColor(const FVector4 & Vector)
    {
        r = Vector.X; g = Vector.Y; b = Vector.Z; a = Vector.W;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        r = (float)(JsonObject->GetNumberField(TEXT("r")));
        g = (float)(JsonObject->GetNumberField(TEXT("g")));
        b = (float)(JsonObject->GetNumberField(TEXT("b")));
        a = (float)(JsonObject->GetNumberField(TEXT("a")));
    }

    static FROSBridgeMsgGeometrymsgsPoint32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPoint32 Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString () const override
    {
        return TEXT("ColorRGBA { r = ") + FString::SanitizeFloat(r) +
                         TEXT(", g = ") + FString::SanitizeFloat(g) +
                         TEXT(", b = ") + FString::SanitizeFloat(b) +
                         TEXT(", a = ") + FString::SanitizeFloat(a) + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("r"), r);
        Object->SetNumberField(TEXT("g"), g);
        Object->SetNumberField(TEXT("b"), b);
        Object->SetNumberField(TEXT("a"), a);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
