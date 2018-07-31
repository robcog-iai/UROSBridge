#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class UInt32 : public FROSBridgeMsg
	{
		uint32 Data;
	public:
		UInt32()
		{
			MsgType = "std_msgs/UInt32";
		}

		UInt32
		(
			uint32 InData
		):
			Data(InData)
		{
			MsgType = "std_msgs/UInt32";
		}

		~UInt32() override {}

		uint32 GetData() const
		{
			return Data;
		}

		void SetData(uint32 InData)
		{
			Data = InData;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Data = JsonObject->GetNumberField(TEXT("data"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Data = BsonObject->GetNumberField(TEXT("data"));

		}

		static UInt32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			UInt32 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static UInt32 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			UInt32 Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("data"), Data);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

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
}