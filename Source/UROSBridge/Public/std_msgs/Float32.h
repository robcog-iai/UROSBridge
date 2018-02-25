#pragma once
#include "ROSBridgeMsg.h"

namespace std_msgs
{
	class Float32 : public FROSBridgeMsg
	{
		float Data;

	public:
		Float32()
		{
			MsgType = "std_msgs/Float32";
		}


		Float32(float InData)
		{
			MsgType = "std_msgs/Float32";
			Data = InData;
		}

		~Float32() override {}

		float GetData()
		{
			return Data;
		}

		void SetData(float InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Data = JsonObject->GetNumberField("data");
		}

		virtual FString ToString() const override
		{
			return TEXT("Float32 { data = \"") + FString::SanitizeFloat(Data) + TEXT("\" }");
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
} // namespace std_msgs#pragma once