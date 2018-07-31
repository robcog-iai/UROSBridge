#pragma once

#include "ROSBridgeMsg.h"


namespace rosgraph_msgs
{
	class Clock : public FROSBridgeMsg
	{
		FROSTime Clock;
	public:
		Clock()
		{
			MsgType = "rosgraph_msgs/Clock";
		}

		Clock
		(
			FROSTime InClock
		):
			Clock(InClock)
		{
			MsgType = "rosgraph_msgs/Clock";
		}

		~Clock() override {}

		FROSTime GetClock() const
		{
			return Clock;
		}

		void SetClock(FROSTime InClock)
		{
			Clock = InClock;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Clock = FROSTime::GetFromJson(JsonObject->GetObjectField(TEXT("clock")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Clock = FROSTime::GetFromBson(BsonObject->GetObjectField(TEXT("clock")));

		}

		static Clock GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Clock Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Clock GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Clock Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("clock"), Clock.ToJsonObject());
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("clock"), Clock.ToBsonObject());
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
}