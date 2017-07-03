#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsString : public FROSBridgeMsg
{
    FString data;

public:
    FROSBridgeMsgStdmsgsString()
    {
        Type = "std_msgs/String";
    }

    FROSBridgeMsgStdmsgsString(FString data_)
    {
        Type = "std_msgs/String";
        data = data_;
    }

    FString GetData()
    {
        return data;
    }

    void SetData(FString str)
    {
        data = str;
    }

    virtual void FromJson(FJsonObject* JsonObject) override {
        data = JsonObject->GetStringField("data");
    }

    virtual FString ToString () override
    {
        return TEXT("String { data = \"" + data + "\" }");
    }

    virtual FString ToYamlString() override {
        FString OutputString;
        FJsonObject Object;
        Object.SetStringField(TEXT("data"), data);

        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
        return OutputString;
    }
};
