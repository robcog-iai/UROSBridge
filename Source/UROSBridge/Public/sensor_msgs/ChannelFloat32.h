#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgSensormsgsChannelFloat32 : public FROSBridgeMsg
{
    FString name; 

public:
    TArray<float> values;

    FROSBridgeMsgSensormsgsChannelFloat32()
    {
        Type = "sensor_msgs/ChannelFloat32";
    }

    FROSBridgeMsgSensormsgsChannelFloat32
    (FString name_, const TArray<float>& values_) :
        name(name_), values(values_)
    {
        Type = "sensor_msgs/ChannelFloat32";
    }

    ~FROSBridgeMsgSensormsgsChannelFloat32() override {}

    FString GetName() const
    {
        return name;
    }

    TArray<float> GetValues() const
    {
        return values;
    }

    void SetName(FString name_)
    {
        name = name_;
    }

    void SetValues(const TArray<float>& values_)
    {
        values = values_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        name = JsonObject->GetStringField(TEXT("name"));
        values.Empty();
        TArray<TSharedPtr<FJsonValue>> ValuesPtrArr = JsonObject->GetArrayField(TEXT("values"));
        for (auto &ptr : ValuesPtrArr)
            values.Add(ptr->AsNumber());
    }

    static FROSBridgeMsgSensormsgsChannelFloat32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgSensormsgsChannelFloat32 Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString() const override
    {
        FString ArrayString = "[ ";
        for (auto &value : values)
            ArrayString += FString::SanitizeFloat(value) + TEXT(", ");
        ArrayString += " ]";

        return TEXT("ChannelFloat32 { name = ") + name +
            TEXT(", values = ") + ArrayString + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

        TArray<TSharedPtr<FJsonValue>> ValArray;
        for (auto &val : values)
            ValArray.Add(MakeShareable<FJsonValue>(new FJsonValueNumber(val)));

        Object->SetStringField(TEXT("name"), name);
        Object->SetArrayField(TEXT("values"), ValArray);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
