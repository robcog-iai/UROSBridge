#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsByte : public FROSBridgeMsg
{
    int8 data;

public:
    FROSBridgeMsgStdmsgsByte()
    {
        MsgType = "std_msgs/Byte";
    }

    FROSBridgeMsgStdmsgsByte(int8 data_)
    {
        MsgType = "std_msgs/Byte";
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

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace std_msgs
{
	class Byte : public FROSBridgeMsg
	{
		int8 Data;

	public:
		Byte()
		{
			MsgType = "std_msgs/Byte";
		}

		Byte(int8 InData)
		{
			MsgType = "std_msgs/Byte";
			Data = InData;
		}

		~Byte() override {}

		int8 GetData()
		{
			return Data;
		}

		void SetData(int8 InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = (Byte)(JsonObject->GetIntegerField("data"));
		}

		virtual FString ToString() const override
		{
			return TEXT("Byte { data = \"" + FString::FromInt(Data) + "\" }");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetNumberField(TEXT("data"), Data);
			return Object;
		}

		virtual FString ToYamlString() const override 
		{
			FString OutputString;
			FJsonObject Object;
			Object.SetNumberField(TEXT("data"), Data);

			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(Object, Writer);
			return OutputString;
		}
	};
} // namespace std_msgs