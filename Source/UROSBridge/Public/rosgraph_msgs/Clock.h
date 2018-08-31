#pragma once

#include "ROSBridgeMsg.h"


namespace rosgraph_msgs
{
	// WARNING!! DO NOT GENERATE THIS CLASS WITH THE AUTOMATiC GENERATOR UNLESS YOU RENAME THE VARIABLE IN THE .MSG FILE FIRST! (call it Time)
	class Clock : public FROSBridgeMsg
	{
		FROSTime Time;
	public:
		Clock()
		{
			MsgType = TEXT("rosgraph_msgs/Clock");
		}
		
		Clock(FROSTime InTime)
			:
			Time(InTime)
		{
			MsgType = TEXT("rosgraph_msgs/Clock");
		}

		~Clock() override {}

		// Getters 
		FROSTime GetClock() const { return Time; }

		// Setters 
		void SetClock(FROSTime InTime) { Time = InTime; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Time = FROSTime::GetFromJson(JsonObject->GetObjectField(TEXT("clock")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Time = FROSTime::GetFromBson(BsonObject->GetObjectField(TEXT("clock")));

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

			Object->SetObjectField(TEXT("clock"), Time.ToJsonObject());

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("clock"), Time.ToBsonObject());

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("Clock { clock = ") + Time.ToString() +
				TEXT(" } ");

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