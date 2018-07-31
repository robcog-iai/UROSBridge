#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/TwistWithCovariance.h"

namespace nav_msgs
{
	class Odometry : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		FString ChildFrameId;
		geometry_msgs::PoseWithCovariance Pose;
		geometry_msgs::TwistWithCovariance Twist;
	public:
		Odometry()
		{
			MsgType = "nav_msgs/Odometry";
		}

		Odometry
		(
			std_msgs::Header InHeader,
			FString InChildFrameId,
			geometry_msgs::PoseWithCovariance InPose,
			geometry_msgs::TwistWithCovariance InTwist
		):
			Header(InHeader),
			ChildFrameId(InChildFrameId),
			Pose(InPose),
			Twist(InTwist)
		{
			MsgType = "nav_msgs/Odometry";
		}

		~Odometry() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		FString GetChildFrameId() const
		{
			return ChildFrameId;
		}

		geometry_msgs::PoseWithCovariance GetPose() const
		{
			return Pose;
		}

		geometry_msgs::TwistWithCovariance GetTwist() const
		{
			return Twist;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetChildFrameId(FString InChildFrameId)
		{
			ChildFrameId = InChildFrameId;
		}

		void SetPose(geometry_msgs::PoseWithCovariance InPose)
		{
			Pose = InPose;
		}

		void SetTwist(geometry_msgs::TwistWithCovariance InTwist)
		{
			Twist = InTwist;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			ChildFrameId = JsonObject->GetStringField(TEXT("child_frame_id"));

			Pose = geometry_msgs::PoseWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));

			Twist = geometry_msgs::TwistWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			ChildFrameId = BsonObject->GetStringField(TEXT("child_frame_id"));

			Pose = geometry_msgs::PoseWithCovariance::GetFromBson(BsonObject->GetObjectField(TEXT("pose")));

			Twist = geometry_msgs::TwistWithCovariance::GetFromBson(BsonObject->GetObjectField(TEXT("twist")));

		}

		static Odometry GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Odometry Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Odometry GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Odometry Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetStringField(TEXT("child_frame_id"), ChildFrameId);
			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
			Object->SetObjectField(TEXT("twist"), Twist.ToJsonObject());
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());
			Object->SetStringField(TEXT("child_frame_id"), ChildFrameId);
			Object->SetObjectField(TEXT("pose"), Pose.ToBsonObject());
			Object->SetObjectField(TEXT("twist"), Twist.ToBsonObject());
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