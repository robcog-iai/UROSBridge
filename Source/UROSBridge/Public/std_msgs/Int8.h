#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsInt8 : public FROSBridgeMsg
{
    int8 data;

public:
    FROSBridgeMsgStdmsgsInt8()
    {
        MsgType = "std_msgs/Int8";
    }

    FROSBridgeMsgStdmsgsInt8(int8 data_)
    {
        MsgType = "std_msgs/Int8";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsInt64() override {}

    int8 GetData()
    {
        return data;
    }

    void SetData(int8 data_)
    {
        data = data_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        data = (int8)(JsonObject->GetIntegerField("data"));
    }

    virtual FString ToString () const override
    {
        return TEXT("Int8 { data = \"" + FString::FromInt(data) + "\" }");
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

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace std_msgs
{
} // namespace std_msgs