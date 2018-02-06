#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/String.h"
#include "std_msgs/Header.h"
namespace sensor_msgs
{
	class JointState : public FROSBridgeMsg
	{
		std_msgs::Header Header;

	public:
		TArray<FString> Names;
		TArray<double> Positions;
		TArray<double> Velocities;
		TArray<double> Efforts;

		JointState()
		{
			MsgType = "sensor_msgs/JointState";
		}

		JointState(
			const std_msgs::Header& InHeader,
			const TArray<FString>& InNames,
			const TArray<double>& InPositions,
			const TArray<double>& InVelocities,
			const TArray<double>& InEfforts) :
			Header(InHeader),
			Names(InNames),
			Positions(InPositions),
			Velocities(InVelocities),
			Efforts(InEfforts)
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
			return Names;
		}

		TArray<double> GetPosition() const 
		{
			return Positions; 
		}
		
		TArray<double> GetVelocity() const 
		{ 
			return Velocities; 
		}

		TArray<double> GetEffort() const 
		{
			return Efforts; 
		}

		void SetHeader(const std_msgs::Header& InHeaders) 
		{
			Header = InHeaders; 
		}

		void SetName(const TArray<FString>& InNames) 
		{
			Names = InNames; 
		}

		void SetPosition(const TArray<double>& InPositions)
		{
			Positions = InPositions; 
		}

		void SetVelocity(const TArray<double>& InVelocities) 
		{
			Velocities = InVelocities;
		}

		void SetEffort(const TArray<double>& InEfforts) 
		{ 
			Efforts = InEfforts; 
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Names.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("name"));
			for (auto &ptr : ValuesPtrArr)
				Names.Add(ptr->AsString());

			Positions.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("position"));
			for (auto &ptr : ValuesPtrArr)
				Positions.Add(ptr->AsNumber());

			Velocities.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("velocity"));
			for (auto &ptr : ValuesPtrArr)
				Velocities.Add(ptr->AsNumber());

			Efforts.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("effort"));
			for (auto &ptr : ValuesPtrArr)
				Efforts.Add(ptr->AsNumber());
		}

		static JointState GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			JointState Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString NamesString = "[ ";
			for (auto &str : Names)
				NamesString += str + TEXT(", ");
			NamesString += " ]";

			FString PositionString = "[ ";
			for (auto &value : Positions)
				PositionString += FString::SanitizeFloat(value) + TEXT(", ");
			PositionString += " ]";

			FString VelocityString = "[ ";
			for (auto &value : Velocities)
				VelocityString += FString::SanitizeFloat(value) + TEXT(", ");
			VelocityString += " ]";

			FString EffortString = "[ ";
			for (auto &value : Efforts)
				EffortString += FString::SanitizeFloat(value) + TEXT(", ");
			EffortString += " ]";

			return TEXT("JointState { header = ") + Header.ToString() +
				TEXT(", name = ") + NamesString +
				TEXT(", position = ") + PositionString +
				TEXT(", velocity = ") + VelocityString +
				TEXT(", effort = ") + EffortString +
				TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> NameArray, PositionArray, VelocityArray, EffortArray;
			for (auto &str : Names)
				NameArray.Add(MakeShareable(new FJsonValueString(str))); // TODO check if FJsonValueString should be used
			for (auto &val : Positions)
				PositionArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : Velocities)
				VelocityArray.Add(MakeShareable(new FJsonValueNumber(val)));
			for (auto &val : Efforts)
				EffortArray.Add(MakeShareable(new FJsonValueNumber(val)));

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetArrayField(TEXT("name"), NameArray);
			Object->SetArrayField(TEXT("position"), PositionArray);
			Object->SetArrayField(TEXT("velocity"), VelocityArray);
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
} // namespace sensor_msgs
