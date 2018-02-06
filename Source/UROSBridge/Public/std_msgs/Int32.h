#pragma once
#include "ROSBridgeMsg.h"

namespace std_msgs
{
	class Int32 : public FROSBridgeMsg
	{
		int32 Data;

	public:
		Int32()
		{
			MsgType = "std_msgs/Int32";
		}


		Int32(int32 InData)
		{
			MsgType = "std_msgs/Int32";
			Data = InData;
		}

		~Int32() override {}

		int32 GetData()
		{
			return Data;
		}

		void SetData(int32 InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Data = JsonObject->GetIntegerField("data");
		}

		virtual FString ToString() const override
		{
			return TEXT("Int32 { data = \"" + FString::FromInt(Data) + "\" }");
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