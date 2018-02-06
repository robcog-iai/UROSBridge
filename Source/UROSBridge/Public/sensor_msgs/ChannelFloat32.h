#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/String.h"

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
		(FString InName, const TArray<float>& InValues) :
			Name(InName), Values(InValues)
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

		void SetValues(const TArray<float>& InValues)
		{
			Values = InValues;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Name = JsonObject->GetStringField(TEXT("name"));
			Values.Empty();
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr = JsonObject->GetArrayField(TEXT("values"));
			for (auto &ptr : ValuesPtrArr)
				Values.Add(ptr->AsNumber());
		}

		static ChannelFloat32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			ChannelFloat32 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayString = "[ ";
			for (auto &value : Values)
				ArrayString += FString::SanitizeFloat(value) + TEXT(", ");
			ArrayString += " ]";

			return TEXT("ChannelFloat32 { name = ") + Name +
				TEXT(", values = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> ValArray;
			for (auto &val : Values)
				ValArray.Add(MakeShareable<FJsonValue>(new FJsonValueNumber(val)));

			Object->SetStringField(TEXT("name"), Name);
			Object->SetArrayField(TEXT("values"), ValArray);
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
} // namespace sensor_msgs