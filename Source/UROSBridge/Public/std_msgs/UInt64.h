#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsUInt64 : public FROSBridgeMsg
{
    uint64 data;

public:
    FROSBridgeMsgStdmsgsUInt64()
    {
        MsgType = "std_msgs/UInt64";
    }


    FROSBridgeMsgStdmsgsUInt64(uint64 data_)
    {
        MsgType = "std_msgs/UInt64";
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


    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        data = (UInt64)(JsonObject->GetNumberField("data"));
    }

    virtual FString ToString () override
    {
        char CharData[21];
        sprintf(CharData, "%llu", data);
        FString StringData(UTF8_TO_TCHAR(CharData));

        return TEXT("UInt64 { data = \"" + StringData + "\" }");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("data"), data);
        return Object;
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

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace std_msgs
{
	class UInt64 : public FROSBridgeMsg
	{
		uint64 Data;

	public:
		UInt64()
		{
			MsgType = "std_msgs/UInt64";
		}


		UInt64(uint64 InData)
		{
			MsgType = "std_msgs/UInt64";
			Data = InData;
		}

		uint64 GetData()
		{
			return Data;
		}

		~UInt64() override {}

		void SetData(uint64 InData)
		{
			Data = InData;
		}


		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = (UInt64)(JsonObject->GetNumberField("data"));
		}

		virtual FString ToString() override
		{
			char CharData[21];
			sprintf(CharData, "%llu", Data);
			FString StringData(UTF8_TO_TCHAR(CharData));

			return TEXT("UInt64 { data = \"" + StringData + "\" }");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetNumberField(TEXT("data"), Data);
			return Object;
		}

		virtual FString ToYamlString() override 
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