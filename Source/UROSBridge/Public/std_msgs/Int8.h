#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Int8 : public FROSBridgeMsg
	{
		int8 Data;
	public:
		Int8()
		{
			MsgType = "std_msgs/Int8";
		}

		Int8
		(
			int8 InData
		):
			Data(InData)
		{
			MsgType = "std_msgs/Int8";
		}

		~Int8() override {}

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

		static Int8 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Int8 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Int8 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Int8 Result;
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