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
		(std_msgs::Header InHeader, geometry_msgs::Pose InPose) :
			Header(InHeader), Pose(InPose)
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

		static PoseStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("PoseStamped { header = ") + Header.ToString() +
				TEXT(", pose = ") + Pose.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
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
} // namespace geometry_msgs