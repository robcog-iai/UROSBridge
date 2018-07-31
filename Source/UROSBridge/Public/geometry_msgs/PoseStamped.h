#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"

namespace geometry_msgs
{
	class PoseStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Pose Pose;
	public:
		PoseStamped()
		{
			MsgType = "geometry_msgs/PoseStamped";
		}

		PoseStamped
		(
			std_msgs::Header InHeader,
			geometry_msgs::Pose InPose
		):
			Header(InHeader),
			Pose(InPose)
		{
			MsgType = "geometry_msgs/PoseStamped";
		}

		~PoseStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Pose GetPose() const
		{
			return Pose;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetPose(geometry_msgs::Pose InPose)
		{
			Pose = InPose;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Pose = geometry_msgs::Pose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Pose = geometry_msgs::Pose::GetFromBson(BsonObject->GetObjectField(TEXT("pose")));

		}

		static PoseStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static PoseStamped GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			PoseStamped Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());
			Object->SetObjectField(TEXT("pose"), Pose.ToBsonObject());
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