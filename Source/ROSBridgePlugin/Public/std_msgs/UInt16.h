#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsUInt16 : public FROSBridgeMsg
{
    uint16 data;

public:
    FROSBridgeMsgStdmsgsUInt16()
    {
        Type = "std_msgs/UInt16";
    }

    FROSBridgeMsgStdmsgsUInt16(uint16 data_)
    {
        Type = "std_msgs/UInt16";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsUInt16() override {}

    uint16 GetData()
    {
        return data;
    }

    void SetData(uint16 data_)
    {
        data = data_;
    }

    virtual void FromJson(const FJsonObject* JsonObject) override {
        data = (int16)(JsonObject->GetIntegerField("data"));
    }

    virtual FString ToString () override
    {
        return TEXT("UInt16 { data = \"" + FString::FromInt(data) + "\" }");
    }

    virtual FString ToYamlString() override {
        FString OutputString;
        FJsonObject Object;
        Object.SetNumberField(TEXT("data"), data);

        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(Object, Writer);
        return OutputString;
    }
};
