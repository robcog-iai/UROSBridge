#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsUInt32 : public FROSBridgeMsg
{
    uint32 data;

public:
    FROSBridgeMsgStdmsgsUint32()
    {
        Type = "std_msgs/UInt32";
    }


    FROSBridgeMsgStdmsgsUInt32(uint32 data_)
    {
        Type = "std_msgs/UInt32";
        data = data_;
    }

    uint32 GetData()
    {
        return data;
    }

    void SetData(uint32 data_)
    {
        data = data_;
    }


    virtual void FromJson(FJsonObject* JsonObject) override {
        data = JsonObject->GetIntegerField("data");
    }

    virtual FString ToString () override
    {
        return TEXT("UInt32 { data = \"" + FString::SanitizeFloat(data) + "\" }");
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
