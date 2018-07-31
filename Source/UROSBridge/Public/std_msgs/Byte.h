#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Byte : public FROSBridgeMsg
	{
		int8 Data;
	public:
		Byte()
		{
			MsgType = "std_msgs/Byte";
		}

		Byte
		(
			int8 InData
		):
			Data(InData)
		{
			MsgType = "std_msgs/Byte";
		}

		~Byte() override {}

		int8 GetData() const
		{
			return Data;
		}

		void SetData(int8 InData)
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

		static Byte GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Byte Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Byte GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Byte Result;
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