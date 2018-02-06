#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/PoseWithCovariance.h"

namespace geometry_msgs
{
	class PoseWithCovarianceStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::PoseWithCovariance Pose;

	public:
		PoseWithCovarianceStamped()
		{
			MsgType = "geometry_msgs/PoseWithCovarianceStamped";
		}

		PoseWithCovarianceStamped
		(std_msgs::Header InHeader, geometry_msgs::PoseWithCovariance InPose) :
			Header(InHeader), Pose(InPose)
		{
			MsgType = "geometry_msgs/PoseWithCovarianceStamped";
		}

		~PoseWithCovarianceStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::PoseWithCovariance GetPose() const
		{
			return Pose;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetPose(geometry_msgs::PoseWithCovariance InPose)
		{
			Pose = InPose;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Pose = geometry_msgs::PoseWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
		}

		static PoseWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseWithCovarianceStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("PoseWithCovarianceStamped { header = ") + Header.ToString() +
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