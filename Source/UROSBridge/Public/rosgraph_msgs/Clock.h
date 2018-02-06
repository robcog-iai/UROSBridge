#pragma once
#include "ROSBridgeMsg.h"

namespace rosgraph_msgs
{
	class Clock : public FROSBridgeMsg
	{
		FROSTime Time;

	public:
		Clock()
		{
			MsgType = "rosgraph_msgs/Clock";
		}

		Clock(FROSTime InTime)
		{
			MsgType = "rosgraph_msgs/Clock";
			Time = InTime;
		}

		~Clock() override {}

		FROSTime GetClock() const
		{
			return Time;
		}

		void SetClock(FROSTime InTime)
		{
			Time = InTime;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Time = FROSTime::GetFromJson(JsonObject->GetObjectField(TEXT("clock")));
		}

		static Clock GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Clock Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Clock { clock = ") + Time.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("clock"), Time.ToJsonObject());
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
} // namespace rosgraph_msgs