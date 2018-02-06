#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsString : public FROSBridgeMsg
{
    FString data;

public:
    FROSBridgeMsgStdmsgsString()
    {
        MsgType = "std_msgs/String";
    }

    FROSBridgeMsgStdmsgsString(FString data_)
    {
        MsgType = "std_msgs/String";
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

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        data = JsonObject->GetStringField("data");
        // UE_LOG(LogTemp, Log, TEXT("In From Json, data: %s"), *data);
    }

	virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
		TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
		Object->SetStringField(TEXT("data"), data); 
		return Object;
	}

	virtual FString ToString() const override
	{
		return TEXT("String { data = \"" + data + "\" }");
	}

    /* virtual FString ToYamlString() const override {
        FString OutputString;
        FJsonObject Object;
        Object.SetStringField(TEXT("data"), data);

        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(MakeShared<FJsonObject>(Object), Writer);
        return OutputString;
    } */ 
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace std_msgs
{
	class String : public FROSBridgeMsg
	{
		FString Data;

	public:
		String()
		{
			MsgType = "std_msgs/String";
		}

		String(FString InData)
		{
			MsgType = "std_msgs/String";
			Data = InData;
		}

		~String() override {}

		FString GetData()
		{
			return Data;
		}

		void SetData(FString InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = JsonObject->GetStringField("data");
		}

		virtual FString ToString() const override
		{
			return TEXT("String { data = \"" + Data + "\" }");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetStringField(TEXT("data"), Data);
			return Object;
		}

		virtual FString ToYamlString() const override 
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
} // namespace std_msgs
