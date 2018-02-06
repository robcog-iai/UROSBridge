#pragma once
#include "ROSBridgeMsg.h"

namespace std_msgs
{
	class UInt16 : public FROSBridgeMsg
	{
		uint16 Data;

	public:
		UInt16()
		{
			MsgType = "std_msgs/UInt16";
		}

		UInt16(uint16 InData)
		{
			MsgType = "std_msgs/UInt16";
			Data = InData;
		}

		~UInt16() override {}

		uint16 GetData()
		{
			return Data;
		}

		void SetData(uint16 InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = (uint16)(JsonObject->GetIntegerField("data"));
		}

		virtual FString ToString() const override
		{
			return TEXT("UInt16 { data = \"" + FString::FromInt(Data) + "\" }");
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