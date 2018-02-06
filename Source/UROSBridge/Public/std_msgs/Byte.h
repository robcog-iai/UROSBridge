#pragma once
#include "ROSBridgeMsg.h"

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