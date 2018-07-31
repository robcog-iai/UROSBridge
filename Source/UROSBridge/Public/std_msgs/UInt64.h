#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class UInt64 : public FROSBridgeMsg
	{
		uint64 Data;
	public:
		UInt64()
		{
			MsgType = "std_msgs/UInt64";
		}

		UInt64
		(
			uint64 InData
		):
			Data(InData)
		{
			MsgType = "std_msgs/UInt64";
		}

		~UInt64() override {}

		uint64 GetData() const
		{
			return Data;
		}

		void SetData(uint64 InData)
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

		static UInt64 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			UInt64 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static UInt64 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			UInt64 Result;
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