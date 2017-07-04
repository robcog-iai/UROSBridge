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

    ~FROSBridgeMsgStdmsgsString() override {}

    FString GetData()
    {
        return data;
    }

    void SetData(FString str)
    {
        data = str;
    }

    virtual void FromJson(const FJsonObject* JsonObject) override {
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
        FJsonSerializer::Serialize(MakeShared<FJsonObject>(Object), Writer);
        return OutputString;
    }
};
