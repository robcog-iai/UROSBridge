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

