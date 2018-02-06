#pragma once
#include "ROSBridgeMsg.h"

namespace std_msgs
{
	class Int64 : public FROSBridgeMsg
	{
		int64 Data;

	public:
		Int64()
		{
			MsgType = "std_msgs/Int64";
		}

		Int64(int64 InData)
		{
			MsgType = "std_msgs/Int64";
			Data = InData;
		}

		~FROSBridgeMsgStdmsgsInt32() override {}

		int64 GetData()
		{
			return Data;
		}

		void SetData(int64 InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = (int64)(JsonObject->GetNumberField("data"));
		}

		virtual FString ToString() const override
		{
			char CharData[21];
			sprintf(CharData, "%lld", Data);
			FString StringData(UTF8_TO_TCHAR(CharData));

			return TEXT("Int64 { data = \"" + StringData + "\" }");
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