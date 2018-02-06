#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsInt16 : public FROSBridgeMsg
{
    int16 data;

public:
    FROSBridgeMsgStdmsgsInt16()
    {
        MsgType = "std_msgs/Int16";
    }

    FROSBridgeMsgStdmsgsInt16(int16 data_)
    {
        MsgType = "std_msgs/Int16";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsInt16() override {}

    int16 GetData()
    {
        return data;
    }

    void SetData(int16 data_)
    {
        data = data_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        data = (int16)(JsonObject->GetIntegerField("data"));
    }

    virtual FString ToString () const override
    {
        return TEXT("Int16 { data = \"" + FString::FromInt(data) + "\" }");
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
	class Int16 : public FROSBridgeMsg
	{
		int16 Data;

	public:
		Int16()
		{
			MsgType = "std_msgs/Int16";
		}

		Int16(int16 InData)
		{
			MsgType = "std_msgs/Int16";
			Data = InData;
		}

		~Int16() override {}

		int16 GetData()
		{
			return Data;
		}

		void SetData(int16 InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = (int16)(JsonObject->GetIntegerField("data"));
		}

		virtual FString ToString() const override
		{
			return TEXT("Int16 { data = \"" + FString::FromInt(Data) + "\" }");
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