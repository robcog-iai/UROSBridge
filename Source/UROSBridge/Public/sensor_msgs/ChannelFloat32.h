#pragma once

#include "ROSBridgeMsg.h"


namespace sensor_msgs
{
	class ChannelFloat32 : public FROSBridgeMsg
	{
		FString Name;
		TArray<float> Values;
	public:
		ChannelFloat32()
		{
			MsgType = "sensor_msgs/ChannelFloat32";
		}

		ChannelFloat32
		(
			FString InName,
			const TArray<float>& InValues
		):
			Name(InName),
			Values(InValues)
		{
			MsgType = "sensor_msgs/ChannelFloat32";
		}

		~ChannelFloat32() override {}

		FString GetName() const
		{
			return Name;
		}

		TArray<float> GetValues() const
		{
			return Values;
		}

		void SetName(FString InName)
		{
			Name = InName;
		}

		void SetValues(TArray<float>& InValues)
		{
			Values = InValues;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Name = JsonObject->GetStringField(TEXT("name"));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Values.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("values"));
			for (auto &ptr : ValuesPtrArr)
				Values.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Name = BsonObject->GetStringField(TEXT("name"));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Values.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("values"));
			for (auto &ptr : ValuesPtrArr)
				Values.Add(ptr->AsNumber());

		}

		static ChannelFloat32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			ChannelFloat32 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static ChannelFloat32 GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			ChannelFloat32 Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetStringField(TEXT("name"), Name);
			TArray<TSharedPtr<FJsonValue>> ValuesArray;
			for (auto &val : Values)
				ValuesArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("values"), ValuesArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetStringField(TEXT("name"), Name);
			TArray<TSharedPtr<FBsonValue>> ValuesArray;
			for (auto &val : Values)
				ValuesArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("values"), ValuesArray);
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