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
			MsgType = "std_msgs/Header";
		}

		Header(
			uint32 InSeq,
			FROSTime InStamp,
			FString InFrameId) :
			Seq(InSeq),
			Stamp(InStamp),
			FrameId(InFrameId)
		{
			MsgType = "std_msgs/Header";
		}

		~Header() override {}

		uint32 GetSeq() const
		{
			return Seq;
		}

		FROSTime GetStamp() const
		{
			return Stamp;
		}

		FString GetFrameId() const
		{
			return FrameId;
		}

		void SetSeq(uint32 InSeq)
		{
			Seq = InSeq;
		}

		void SetStamp(FROSTime InStamp)
		{
			Stamp = InStamp;
		}

		void SetFrameId(FString InFrameId)
		{
			FrameId = InFrameId;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Seq = (uint32)(JsonObject->GetNumberField(TEXT("seq")));
			Stamp = FROSTime::GetFromJson(JsonObject->GetObjectField(TEXT("stamp")));
			FrameId = JsonObject->GetStringField(TEXT("frame_id"));
		}

		static Header GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Header Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Header { seq = ") + FString::FromInt(Seq) +
				TEXT(", stamp = ") + Stamp.ToString() +
				TEXT(", frame_id = ") + FrameId + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetNumberField(TEXT("seq"), Seq);
			Object->SetObjectField(TEXT("stamp"), Stamp.ToJsonObject());
			Object->SetStringField(TEXT("frame_id"), FrameId);
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
