#pragma once
#include "ROSBridgeMsg.h"

namespace std_msgs
{
	class UInt32 : public FROSBridgeMsg
	{
		uint32 Data;

	public:
		UInt32()
		{
			MsgType = "std_msgs/UInt32";
		}


		UInt32(uint32 InData)
		{
			MsgType = "std_msgs/UInt32";
			Data = InData;
		}

		~UInt32() override {}

		uint32 GetData()
		{
			return Data;
		}

		void SetData(uint32 InData)
		{
			Data = InData;
		}


		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = JsonObject->GetIntegerField("data");
		}

		virtual FString ToString() const override
		{
			return TEXT("UInt32 { data = \"" + FString::SanitizeFloat(Data) + "\" }");
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