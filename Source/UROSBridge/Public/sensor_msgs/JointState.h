#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"

namespace sensor_msgs
{
	class JointState : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		TArray<FString> Name;
		TArray<double> Position;
		TArray<double> Velocity;
		TArray<double> Effort;
	public:
		JointState()
		{
			MsgType = "sensor_msgs/JointState";
		}

		JointState
		(
			std_msgs::Header InHeader,
			const TArray<FString>& InName,
			const TArray<double>& InPosition,
			const TArray<double>& InVelocity,
			const TArray<double>& InEffort
		):
			Header(InHeader),
			Name(InName),
			Position(InPosition),
			Velocity(InVelocity),
			Effort(InEffort)
		{
			MsgType = "sensor_msgs/JointState";
		}

		~JointState() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		TArray<FString> GetName() const
		{
			return Name;
		}

		TArray<double> GetPosition() const
		{
			return Position;
		}

		TArray<double> GetVelocity() const
		{
			return Velocity;
		}

		TArray<double> GetEffort() const
		{
			return Effort;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetName(TArray<FString>& InName)
		{
			Name = InName;
		}

		void SetPosition(TArray<double>& InPosition)
		{
			Position = InPosition;
		}

		void SetVelocity(TArray<double>& InVelocity)
		{
			Velocity = InVelocity;
		}

		void SetEffort(TArray<double>& InEffort)
		{
			Effort = InEffort;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Name.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("name"));
			for (auto &ptr : ValuesPtrArr)
				Name.Add(ptr->AsString());

			Position.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("position"));
			for (auto &ptr : ValuesPtrArr)
				Position.Add(ptr->AsNumber());

			Velocity.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("velocity"));
			for (auto &ptr : ValuesPtrArr)
				Velocity.Add(ptr->AsNumber());

			Effort.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("effort"));
			for (auto &ptr : ValuesPtrArr)
				Effort.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Name.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("name"));
			for (auto &ptr : ValuesPtrArr)
				Name.Add(ptr->AsString());

			Position.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("position"));
			for (auto &ptr : ValuesPtrArr)
				Position.Add(ptr->AsNumber());

			Velocity.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("velocity"));
			for (auto &ptr : ValuesPtrArr)
				Velocity.Add(ptr->AsNumber());

			Effort.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("effort"));
			for (auto &ptr : ValuesPtrArr)
				Effort.Add(ptr->AsNumber());

		}

		static JointState GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			JointState Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static JointState GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			JointState Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			TArray<TSharedPtr<FJsonValue>> NameArray;
			for (auto &val : Name)
				NameArray.Add(MakeShareable(new FJsonValueString(val)));
			Object->SetArrayField(TEXT("name"), NameArray);
			TArray<TSharedPtr<FJsonValue>> PositionArray;
			for (auto &val : Position)
				PositionArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("position"), PositionArray);
			TArray<TSharedPtr<FJsonValue>> VelocityArray;
			for (auto &val : Velocity)
				VelocityArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("velocity"), VelocityArray);
			TArray<TSharedPtr<FJsonValue>> EffortArray;
			for (auto &val : Effort)
				EffortArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("effort"), EffortArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());
			TArray<TSharedPtr<FBsonValue>> NameArray;
			for (auto &val : Name)
				NameArray.Add(MakeShareable(new FBsonValueString(val)));
			Object->SetArrayField(TEXT("name"), NameArray);
			TArray<TSharedPtr<FBsonValue>> PositionArray;
			for (auto &val : Position)
				PositionArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("position"), PositionArray);
			TArray<TSharedPtr<FBsonValue>> VelocityArray;
			for (auto &val : Velocity)
				VelocityArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("velocity"), VelocityArray);
			TArray<TSharedPtr<FBsonValue>> EffortArray;
			for (auto &val : Effort)
				EffortArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("effort"), EffortArray);
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