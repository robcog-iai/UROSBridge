#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsUInt64 : public FROSBridgeMsg
{
    uint64 data;

public:
    FROSBridgeMsgStdmsgsUInt64()
    {
        Type = "std_msgs/UInt64";
    }


    FROSBridgeMsgStdmsgsUInt64(uint64 data_)
    {
        Type = "std_msgs/UInt64";
        data = data_;
    }

    uint64 GetData()
    {
        return data;
    }

    ~FROSBridgeMsgStdmsgsUInt64() override {}

    void SetData(uint64 data_)
    {
        data = data_;
    }


    virtual void FromJson(const FJsonObject* JsonObject) override {
        data = (UInt64)(JsonObject->GetNumberField("data"));
    }

    virtual FString ToString () override
    {
        char CharData[21];
        sprintf(CharData, "%llu", data);
        FString StringData(UTF8_TO_TCHAR(CharData));

        return TEXT("UInt64 { data = \"" + StringData + "\" }");
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
