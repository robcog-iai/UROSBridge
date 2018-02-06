#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsUInt8 : public FROSBridgeMsg
{
    uint8 data;

public:
    FROSBridgeMsgStdmsgsUInt8()
    {
        MsgType = "std_msgs/UInt8";
    }


    FROSBridgeMsgStdmsgsUInt8(uint8 data_)
    {
        MsgType = "std_msgs/UInt8";
        data = data_;
    }

    ~FROSBridgeMsgStdmsgsUInt8() override {}

    uint8 GetData()
    {
        return data;
    }

    void SetData(uint8 data_)
    {
        data = data_;
    }


    virtual void FromJson(FJsonObject* JsonObject) override {
        data = (UInt8)(JsonObject->GetIntegerField("data"));
    }

    virtual FString ToString () const override
    {
        return TEXT("UInt8 { data = \"" + FString::FromInt(data) + "\" }");
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
        FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
        return OutputString;
    }
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace std_msgs
{
	class UInt8 : public FROSBridgeMsg
	{
		uint8 Data;

	public:
		UInt8()
		{
			MsgType = "std_msgs/UInt8";
		}


		UInt8(uint8 InData)
		{
			MsgType = "std_msgs/UInt8";
			Data = InData;
		}

		~UInt8() override {}

		uint8 GetData()
		{
			return Data;
		}

		void SetData(uint8 InData)
		{
			Data = InData;
		}


		virtual void FromJson(FJsonObject* JsonObject) override 
		{
			Data = (UInt8)(JsonObject->GetIntegerField("data"));
		}

		virtual FString ToString() const override
		{
			return TEXT("UInt8 { data = \"" + FString::FromInt(Data) + "\" }");
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
			FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
			return OutputString;
		}
	};
} // namespace std_msgs