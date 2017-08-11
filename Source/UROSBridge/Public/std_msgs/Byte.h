#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsByte : public FROSBridgeMsg
{
    int8 data;

public:
    FROSBridgeMsgStdmsgsByte()
    {
        Type = "std_msgs/Byte";
    }

    FROSBridgeMsgStdmsgsByte(int8 data_)
    {
        Type = "std_msgs/Byte";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsByte() override {}

    int8 GetData()
    {
        return data;
    }

    void SetData(int8 data_)
    {
        data = data_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        data = (Byte)(JsonObject->GetIntegerField("data"));
    }

    virtual FString ToString () const override
    {
        return TEXT("Byte { data = \"" + FString::FromInt(data) + "\" }");
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
