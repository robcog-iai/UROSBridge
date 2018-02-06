#pragma once
#include "ROSBridgeMsg.h"

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
