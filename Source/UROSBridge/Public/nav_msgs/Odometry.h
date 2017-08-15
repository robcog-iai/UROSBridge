#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/TwistWithCovariance.h"

class FROSBridgeMsgNavmsgsOdometry : public FROSBridgeMsg
{
	FROSBridgeMsgStdmsgsHeader header;
	FROSBridgeMsgStdmsgsString child_frame_id;
	FROSBridgeMsgGeometrymsgsPoseWithCovariance pose;
	FROSBridgeMsgGeometrymsgsTwistWithCovariance twist;

public:
	FROSBridgeMsgNavmsgsOdometry()
	{
		Type = "nav_msgs/Odometry";
	}

	FROSBridgeMsgNavmsgsOdometry
		(FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgStdmsgsString child_frame_id_,
			FROSBridgeMsgGeometrymsgsPoseWithCovariance pose_,
			FROSBridgeMsgGeometrymsgsTwistWithCovariance twist_) :
		header(header_), child_frame_id(child_frame_id_), pose(pose_), twist(twist_)
	{
		Type = "nav_msgs/Odometry";
	}

	~FROSBridgeMsgNavmsgsOdometry() override {}

	FROSBridgeMsgStdmsgsHeader GetHeader() const { return header; }
	FROSBridgeMsgStdmsgsString GetChildFrameId() const { return child_frame_id; }
	FROSBridgeMsgGeometrymsgsPoseWithCovariance GetPose() { return pose; }
	FROSBridgeMsgGeometrymsgsTwistWithCovariance GetTwist() { return twist; }

	void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
	{
		header = header_;
	}

	void SetString(FROSBridgeMsgStdmsgsString child_frame_id_)
	{
		child_frame_id = child_frame_id_;
	}

	void SetPose(FROSBridgeMsgGeometrymsgsPoseWithCovariance pose_)
	{
		pose = pose_;
	}

	void SetTwist(FROSBridgeMsgGeometrymsgsTwistWithCovariance twist_)
	{
		twist = twist_;
	}

	virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
	{
		header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
		// is this string correct?
		child_frame_id = FROSBridgeMsgStdmsgsString(JsonObject->GetStringField("child_frame_id"));
		pose = FROSBridgeMsgGeometrymsgsPoseWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
		twist = FROSBridgeMsgGeometrymsgsTwistWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));
	}

	static FROSBridgeMsgNavmsgsOdometry GetFromJson(TSharedPtr<FJsonObject> JsonObject)
	{
		FROSBridgeMsgNavmsgsOdometry Result;
		Result.FromJson(JsonObject);
		return Result;
	}

	virtual FString ToString() const override
	{
		return TEXT("Odometry { header = ") + header.ToString() +
			TEXT(", child_frame_id = ") + child_frame_id.ToString() +
			TEXT(", pose = ") + pose.ToString() +
			TEXT(", twist = ") + twist.ToString() +
			TEXT(" } ");
	}

	virtual TSharedPtr<FJsonObject> ToJsonObject() const override
	{
		TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
		Object->SetObjectField(TEXT("header"), header.ToJsonObject());
		Object->SetObjectField(TEXT("child_frame_id"), child_frame_id.ToJsonObject());
		Object->SetObjectField(TEXT("pose"), pose.ToJsonObject());
		Object->SetObjectField(TEXT("twist"), twist.ToJsonObject());
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