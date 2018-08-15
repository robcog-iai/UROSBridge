#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Header : public FROSBridgeMsg
	{
		uint32 Seq;
		FROSTime Stamp;
		FString FrameId;
	public:
		Header()
		{
			MsgType = TEXT("std_msgs/Header");
		}
		
		Header(uint32 InSeq,
			FROSTime InStamp,
			FString InFrameId)
			:
			Seq(InSeq),
			Stamp(InStamp),
			FrameId(InFrameId)
		{
			MsgType = TEXT("std_msgs/Header");
		}

		~Header() override {}

		// Getters 
		uint32 GetSeq() const { return Seq; }
		FROSTime GetStamp() const { return Stamp; }
		FString GetFrameId() const { return FrameId; }

		// Setters 
		void SetSeq(uint32 InSeq) { Seq = InSeq; }
		void SetStamp(FROSTime InStamp) { Stamp = InStamp; }
		void SetFrameId(FString InFrameId) { FrameId = InFrameId; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Seq = JsonObject->GetNumberField(TEXT("seq"));

			Stamp = FROSTime::GetFromJson(JsonObject->GetObjectField(TEXT("stamp")));

			FrameId = JsonObject->GetStringField(TEXT("frame_id"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Seq = BsonObject->GetNumberField(TEXT("seq"));

			Stamp = FROSTime::GetFromBson(BsonObject->GetObjectField(TEXT("stamp")));

			FrameId = BsonObject->GetStringField(TEXT("frame_id"));

		}

		static Header GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Header Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Header GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Header Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("seq"), Seq);

			Object->SetObjectField(TEXT("stamp"), Stamp.ToJsonObject());

			Object->SetStringField(TEXT("frame_id"), FrameId);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetNumberField(TEXT("seq"), Seq);

			Object->SetObjectField(TEXT("stamp"), Stamp.ToBsonObject());

			Object->SetStringField(TEXT("frame_id"), FrameId);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("Header { seq = ") + FString::FromInt(Seq) +
				TEXT(", stamp = ") + Stamp.ToString() +
				TEXT(", frame_id = ") + FrameId +
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