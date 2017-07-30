#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgStdmsgsHeader : public FROSBridgeMsg
{
	uint32 seq; 
	FROSTime stamp; 
	FString frame_id; 

public:
    FROSBridgeMsgStdmsgsHeader()
    {
        Type = "std_msgs/Header";
    }

    FROSBridgeMsgStdmsgsHeader(uint32 seq_, FROSTime stamp_, FString frame_id_)
    {
        Type = "std_msgs/Header";
		seq = seq_; 
		stamp = stamp_; 
		frame_id = frame_id_; 
    }

	~FROSBridgeMsgStdmsgsHeader() override {}

    uint32 GetSeq() const 
    {
        return seq;
    }

	FROSTime GetStamp() const 
	{
		return stamp; 
	}

	FString GetFrameId() const
	{
		return frame_id; 
	}

    void SetSeq(uint32 seq_)
    {
        seq = seq_;
    }

	void SetStamp(FROSTime stamp_)
	{
		stamp = stamp_;
	}

	void SetFrameId(FString frame_id_)
	{
		frame_id = frame_id_;
	}

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
		seq = (uint32)(JsonObject->GetNumberField(TEXT("seq"))); 
		stamp = FROSTime::GetFromJson(JsonObject->GetObjectField(TEXT("stamp")));
		frame_id = JsonObject->GetStringField(TEXT("frame_id")); 
    }

	static FROSBridgeMsgStdmsgsHeader GetFromJson(TSharedPtr<FJsonObject> JsonObject)
	{
		FROSBridgeMsgStdmsgsHeader Result; 
		Result.FromJson(JsonObject); 
		return Result; 
	}

    virtual FString ToString () const override
    {
        return TEXT("Header { seq = ") + FString::FromInt(seq) + 
			        TEXT(", stamp = ") + stamp.ToString() + 
			     TEXT(", frame_id = ") + frame_id + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
		TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
		Object->SetNumberField(TEXT("seq"), seq);
		Object->SetObjectField(TEXT("stamp"), stamp.ToJsonObject()); 
		Object->SetStringField(TEXT("frame_id"), frame_id); 
		return Object;
	}

    virtual FString ToYamlString() const override {
		FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
