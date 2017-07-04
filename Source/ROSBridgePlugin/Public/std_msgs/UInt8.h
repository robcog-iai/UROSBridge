#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsUInt8 : public FROSBridgeMsg
{
    uint8 data;

public:
    FROSBridgeMsgStdmsgsUInt8()
    {
        Type = "std_msgs/UInt8";
    }


    FROSBridgeMsgStdmsgsUInt8(uint8 data_)
    {
        Type = "std_msgs/UInt8";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsUInt8() override {}

    uint8 GetData()
    {
        return data;
    }

    void SetData(uint8 data_)
    {
        data = data_;
    }


    virtual void FromJson(FJsonObject* JsonObject) override {
        data = (UInt8)(JsonObject->GetIntegerField("data"));
    }

    virtual FString ToString () override
    {
        return TEXT("UInt8 { data = \"" + FString::FromInt(data) + "\" }");
    }

    virtual FString ToYamlString() override {
        FString OutputString;
        FJsonObject Object;
        Object.SetNumberField(TEXT("data"), data);

        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
        return OutputString;
    }
};
