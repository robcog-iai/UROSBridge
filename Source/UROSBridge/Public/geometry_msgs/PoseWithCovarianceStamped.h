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
			MsgType = TEXT("geometry_msgs/PoseWithCovarianceStamped");
		}
		
		PoseWithCovarianceStamped(std_msgs::Header InHeader,
			geometry_msgs::PoseWithCovariance InPose)
			:
			Header(InHeader),
			Pose(InPose)
		{
			MsgType = TEXT("geometry_msgs/PoseWithCovarianceStamped");
		}

		~PoseWithCovarianceStamped() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		geometry_msgs::PoseWithCovariance GetPose() const { return Pose; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetPose(geometry_msgs::PoseWithCovariance InPose) { Pose = InPose; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Pose = geometry_msgs::PoseWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Pose = geometry_msgs::PoseWithCovariance::GetFromBson(BsonObject->GetObjectField(TEXT("pose")));

		}

		static PoseWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseWithCovarianceStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static PoseWithCovarianceStamped GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			PoseWithCovarianceStamped Result;
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

		virtual FString ToString() const override
		{
							
			return TEXT("PoseWithCovarianceStamped { header = ") + Header.ToString() +
				TEXT(", pose = ") + Pose.ToString() +
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