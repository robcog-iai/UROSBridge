#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsUInt32 : public FROSBridgeMsg
{
    uint32 data;

public:
    FROSBridgeMsgStdmsgsUInt32()
    {
        Type = "std_msgs/UInt32";
    }


    FROSBridgeMsgStdmsgsUInt32(uint32 data_)
    {
        Type = "std_msgs/UInt32";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsUInt32() override {}

    uint32 GetData()
    {
        return data;
    }

    void SetData(uint32 data_)
    {
        data = data_;
    }


    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        data = JsonObject->GetIntegerField("data");
    }

    virtual FString ToString () const override
    {
        return TEXT("UInt32 { data = \"" + FString::SanitizeFloat(data) + "\" }");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("data"), data);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString;
        FJsonObject Object;
        Object.SetNumberField(TEXT("data"), data);

        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(Object, Writer);
        return OutputString;
    }
};
