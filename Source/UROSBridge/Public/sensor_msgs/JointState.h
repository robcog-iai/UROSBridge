#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"

class FROSBridgeMsgSensormsgsJointState : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header; 

public:
    TArray<FString> name;
    TArray<double > position;
    TArray<double > velocity;
    TArray<double > effort;

    FROSBridgeMsgSensormsgsJointState()
    {
        Type = "sensor_msgs/JointState";
    }

    FROSBridgeMsgSensormsgsJointState
    (const FROSBridgeMsgStdmsgsHeader& header_, const TArray<FString>& name_, const TArray<double>& position_,
        const TArray<double>& velocity_, const TArray<double>& effort_) :
        header(header_), name(name_), position(position_), velocity(velocity_), effort(effort_)
    {
        Type = "sensor_msgs/JointState";
    }

    ~FROSBridgeMsgSensormsgsJointState() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const { return header; }
    TArray<FString> GetName() const { return name; }
    TArray<double> GetPosition() const { return position; }
    TArray<double> GetVelocity() const { return velocity; }
    TArray<double> GetEffort() const { return effort; }

    void SetHeader(const FROSBridgeMsgStdmsgsHeader& header_) { header = header_; }
    void SetName(const TArray<FString>& name_) { name = name_; }
    void SetPosition(const TArray<double>& position_) { position = position_; }
    void SetVelocity(const TArray<double>& velocity_) { velocity = velocity_; }
    void SetEffort(const TArray<double>& effort_) { effort = effort_; }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

        name.Empty();
        ValuesPtrArr = JsonObject->GetArrayField(TEXT("name"));
        for (auto &ptr : ValuesPtrArr)
            name.Add(ptr->AsString());

        position.Empty();
        ValuesPtrArr = JsonObject->GetArrayField(TEXT("position"));
        for (auto &ptr : ValuesPtrArr)
            position.Add(ptr->AsNumber());

        velocity.Empty();
        ValuesPtrArr = JsonObject->GetArrayField(TEXT("velocity"));
        for (auto &ptr : ValuesPtrArr)
            velocity.Add(ptr->AsNumber());

        effort.Empty();
        ValuesPtrArr = JsonObject->GetArrayField(TEXT("effort")); 
        for (auto &ptr : ValuesPtrArr)
            effort.Add(ptr->AsNumber());
    }

    static FROSBridgeMsgSensormsgsJointState GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgSensormsgsJointState Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString() const override
    {
        FString NamesString = "[ ";
        for (auto &str : name)
            NamesString += str + TEXT(", ");
        NamesString += " ]";

        FString PositionString = "[ ";
        for (auto &value : position)
            PositionString += FString::SanitizeFloat(value) + TEXT(", ");
        PositionString += " ]";

        FString VelocityString = "[ ";
        for (auto &value : velocity)
            VelocityString += FString::SanitizeFloat(value) + TEXT(", ");
        VelocityString += " ]";

        FString EffortString = "[ ";
        for (auto &value : effort)
            EffortString += FString::SanitizeFloat(value) + TEXT(", ");
        EffortString += " ]";

        return TEXT("JointState { header = ") + header.ToString() +
            TEXT(", name = ") + NamesString +
            TEXT(", position = ") + PositionString +
            TEXT(", velocity = ") + VelocityString +
            TEXT(", effort = ") + EffortString +
            TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

        TArray<TSharedPtr<FJsonValue>> NameArray, PositionArray, VelocityArray, EffortArray;
        for (auto &str : name)
            NameArray.Add(MakeShareable(new FJsonValueString(str)));
        for (auto &val : position)
            PositionArray.Add(MakeShareable(new FJsonValueNumber(val)));
        for (auto &val : velocity)
            VelocityArray.Add(MakeShareable(new FJsonValueNumber(val)));
        for (auto &val : effort)
            EffortArray.Add(MakeShareable(new FJsonValueNumber(val)));

        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetArrayField(TEXT("name"), NameArray);
        Object->SetArrayField(TEXT("position"), PositionArray);
        Object->SetArrayField(TEXT("velocity"), VelocityArray);
        Object->SetArrayField(TEXT("effort"), EffortArray);
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
			Type = "sensor_msgs/JointState";
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
			Type = "sensor_msgs/JointState";
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
				NameArray.Add(MakeShareable(new FJsonValueString(str)));
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
}
