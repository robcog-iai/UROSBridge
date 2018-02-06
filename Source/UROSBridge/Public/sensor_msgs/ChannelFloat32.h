#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/String.h"

class FROSBridgeMsgSensormsgsChannelFloat32 : public FROSBridgeMsg
{
    FString name; 

public:
    TArray<float> values;

    FROSBridgeMsgSensormsgsChannelFloat32()
    {
        MsgType = "sensor_msgs/ChannelFloat32";
    }

    FROSBridgeMsgSensormsgsChannelFloat32
    (FString name_, const TArray<float>& values_) :
        name(name_), values(values_)
    {
        MsgType = "sensor_msgs/ChannelFloat32";
    }

    ~FROSBridgeMsgSensormsgsChannelFloat32() override {}

    FString GetName() const
    {
        return name;
    }

    TArray<float> GetValues() const
    {
        return values;
    }

    void SetName(FString name_)
    {
        name = name_;
    }

    void SetValues(const TArray<float>& values_)
    {
        values = values_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        name = JsonObject->GetStringField(TEXT("name"));
        values.Empty();
        TArray<TSharedPtr<FJsonValue>> ValuesPtrArr = JsonObject->GetArrayField(TEXT("values"));
        for (auto &ptr : ValuesPtrArr)
            values.Add(ptr->AsNumber());
    }

    static FROSBridgeMsgSensormsgsChannelFloat32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgSensormsgsChannelFloat32 Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString() const override
    {
        FString ArrayString = "[ ";
        for (auto &value : values)
            ArrayString += FString::SanitizeFloat(value) + TEXT(", ");
        ArrayString += " ]";

        return TEXT("ChannelFloat32 { name = ") + name +
            TEXT(", values = ") + ArrayString + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

        TArray<TSharedPtr<FJsonValue>> ValArray;
        for (auto &val : values)
            ValArray.Add(MakeShareable<FJsonValue>(new FJsonValueNumber(val)));

        Object->SetStringField(TEXT("name"), name);
        Object->SetArrayField(TEXT("values"), ValArray);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
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