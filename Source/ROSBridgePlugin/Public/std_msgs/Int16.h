#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsInt16 : public FROSBridgeMsg
{
    int16 data;

public:
    FROSBridgeMsgStdmsgsString()
    {
        Type = "std_msgs/Int16";
    }

    FROSBridgeMsgStdmsgsInt16(int16 data_)
    {
        Type = "std_msgs/Int16";
        data = data_;
    }

    int16 GetData()
    {
        return data;
    }

    void SetData(int16 data_)
    {
        data = data_;
    }

    virtual void FromJson(FJsonObject* JsonObject) override {
        data = (int16)(JsonObject->GetIntegerField("data"));
    }

    virtual FString ToString () override
    {
        return TEXT("Int16 { data = \"" + FString::FromInt(data) + "\" }");
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
