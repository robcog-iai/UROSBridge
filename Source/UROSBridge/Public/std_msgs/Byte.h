#pragma once
#include "ROSBridgeMsg.h"

namespace std_msgs
{
	class Byte : public FROSBridgeMsg
	{
		uint8 Data;

	public:
		Byte()
		{
			MsgType = "std_msgs/Byte";
		}

		Byte(uint8 InData)
		{
			MsgType = "std_msgs/Byte";
			Data = InData;
		}

		~Byte() override {}

		int8 GetData()
		{
			return Data;
		}

		void SetData(uint8 InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
                  Data = JsonObject->GetIntegerField("data");
                }

		static Byte GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Byte Result;
			Result.FromJson(JsonObject);
			return Result;
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

			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
} // namespace std_msgs
