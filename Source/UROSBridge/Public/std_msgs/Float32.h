#pragma once

#include "ROSBridgeMsg.h"


namespace std_msgs
{
	class Float32 : public FROSBridgeMsg
	{
		float Data;
	public:
		Float32()
		{
			MsgType = "std_msgs/Float32";
		}

		Float32
		(
			float InData
		):
			Data(InData)
		{
			MsgType = "std_msgs/Float32";
		}

		~Float32() override {}

		float GetData() const
		{
			return Data;
		}

		void SetData(float InData)
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

		static Float32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Float32 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Float32 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Float32 Result;
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