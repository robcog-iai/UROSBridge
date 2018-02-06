#pragma once
#include "ROSBridgeMsg.h"

namespace std_msgs
{

	class Int8 : public FROSBridgeMsg
	{
		int8 Data;

	public:
		Int8()
		{
			MsgType = "std_msgs/Int8";
		}

		Int8(int8 InData)
		{
			MsgType = "std_msgs/Int8";
			Data = InData;
		}

		~Int8() override {}

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
			Data = (int8)(JsonObject->GetIntegerField("data"));
		}

		virtual FString ToString() const override
		{
			return TEXT("Int8 { data = \"" + FString::FromInt(Data) + "\" }");
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