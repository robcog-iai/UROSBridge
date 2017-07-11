#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsInt32 : public FROSBridgeMsg
{
    int32 data;

public:
    FROSBridgeMsgStdmsgsInt32()
    {
        Type = "std_msgs/Int32";
    }


    FROSBridgeMsgStdmsgsInt32(int32 data_)
    {
        Type = "std_msgs/Int32";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsInt32() override {}

    int32 GetData()
    {
        return data;
    }

    void SetData(int32 data_)
    {
        data = data_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        data = JsonObject->GetIntegerField("data");
    }

    virtual FString ToString () const override
    {
        return TEXT("Int32 { data = \"" + FString::FromInt(data) + "\" }");
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
