#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Int64 : public FROSBridgeMsg
	{
		int64 Data;
	public:
		Int64()
		{
			MsgType = "std_msgs/Int64";
		}

		Int64
		(
			int64 InData
		):
			Data(InData)
		{
			MsgType = "std_msgs/Int64";
		}

		~Int64() override {}

		int64 GetData() const
		{
			return Data;
		}

		void SetData(int64 InData)
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

		static Int64 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Int64 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Int64 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Int64 Result;
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