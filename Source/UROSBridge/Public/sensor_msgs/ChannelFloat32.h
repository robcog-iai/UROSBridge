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
			MsgType = TEXT("sensor_msgs/ChannelFloat32");
		}
		
		ChannelFloat32(FString InName,
			TArray<float> InValues)
			:
			Name(InName),
			Values(InValues)
		{
			MsgType = TEXT("sensor_msgs/ChannelFloat32");
		}

		~ChannelFloat32() override {}

		// Getters 
		FString GetName() const { return Name; }
		TArray<float> GetValues() const { return Values; }

		// Setters 
		void SetName(FString InName) { Name = InName; }
		void SetValues(TArray<float> InValues) { Values = InValues; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Name = JsonObject->GetStringField(TEXT("name"));

			Values.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("values"));
			for (auto &ptr : ValuesPtrArr)
				Values.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Name = BsonObject->GetStringField(TEXT("name"));

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

		virtual FString ToString() const override
		{
							
			FString ValuesString = "[ ";
			for (auto &value : Values)
				ValuesString += FString::SanitizeFloat(value) + TEXT(", ");
			ValuesString += " ] ";
			return TEXT("ChannelFloat32 { name = ") + Name +
				TEXT(", values =") + ValuesString +
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