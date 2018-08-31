#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"


namespace sensor_msgs
{
	class JointState : public FROSBridgeMsg
	{
		std_msgs::Header Header;
	public:
		// WARNING! Will be private when the generator is used again. Use Getters and Setters instead of direct access.
		TArray<FString> Name;
		// WARNING! Will be private when the generator is used again. Use Getters and Setters instead of direct access.
		TArray<double> Position;
		// WARNING! Will be private when the generator is used again. Use Getters and Setters instead of direct access.
		TArray<double> Velocity;
		// WARNING! Will be private when the generator is used again. Use Getters and Setters instead of direct access.
		TArray<double> Effort;
		
		JointState()
		{
			MsgType = TEXT("sensor_msgs/JointState");
		}
		
		JointState(std_msgs::Header InHeader,
			TArray<FString> InName,
			TArray<double> InPosition,
			TArray<double> InVelocity,
			TArray<double> InEffort)
			:
			Header(InHeader),
			Name(InName),
			Position(InPosition),
			Velocity(InVelocity),
			Effort(InEffort)
		{
			MsgType = TEXT("sensor_msgs/JointState");
		}

		~JointState() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		TArray<FString> GetName() const { return Name; }
		TArray<double> GetPosition() const { return Position; }
		TArray<double> GetVelocity() const { return Velocity; }
		TArray<double> GetEffort() const { return Effort; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetName(TArray<FString> InName) { Name = InName; }
		void SetPosition(TArray<double> InPosition) { Position = InPosition; }
		void SetVelocity(TArray<double> InVelocity) { Velocity = InVelocity; }
		void SetEffort(TArray<double> InEffort) { Effort = InEffort; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

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
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

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

		virtual FString ToString() const override
		{
							
			FString NameString = "[ ";
			for (auto &value : Name)
				NameString += value + TEXT(", ");
			NameString += " ] ";
			FString PositionString = "[ ";
			for (auto &value : Position)
				PositionString += FString::SanitizeFloat(value) + TEXT(", ");
			PositionString += " ] ";
			FString VelocityString = "[ ";
			for (auto &value : Velocity)
				VelocityString += FString::SanitizeFloat(value) + TEXT(", ");
			VelocityString += " ] ";
			FString EffortString = "[ ";
			for (auto &value : Effort)
				EffortString += FString::SanitizeFloat(value) + TEXT(", ");
			EffortString += " ] ";
			return TEXT("JointState { header = ") + Header.ToString() +
				TEXT(", name =") + NameString +
				TEXT(", position =") + PositionString +
				TEXT(", velocity =") + VelocityString +
				TEXT(", effort =") + EffortString +
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