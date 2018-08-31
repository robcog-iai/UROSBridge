#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/TwistWithCovariance.h"


namespace geometry_msgs
{
	class TwistWithCovarianceStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::TwistWithCovariance Twist;
	public:
		TwistWithCovarianceStamped()
		{
			MsgType = TEXT("geometry_msgs/TwistWithCovarianceStamped");
		}
		
		TwistWithCovarianceStamped(std_msgs::Header InHeader,
			geometry_msgs::TwistWithCovariance InTwist)
			:
			Header(InHeader),
			Twist(InTwist)
		{
			MsgType = TEXT("geometry_msgs/TwistWithCovarianceStamped");
		}

		~TwistWithCovarianceStamped() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		geometry_msgs::TwistWithCovariance GetTwist() const { return Twist; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetTwist(geometry_msgs::TwistWithCovariance InTwist) { Twist = InTwist; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Twist = geometry_msgs::TwistWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Twist = geometry_msgs::TwistWithCovariance::GetFromBson(BsonObject->GetObjectField(TEXT("twist")));

		}

		static TwistWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TwistWithCovarianceStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static TwistWithCovarianceStamped GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			TwistWithCovarianceStamped Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());

			Object->SetObjectField(TEXT("twist"), Twist.ToJsonObject());

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());

			Object->SetObjectField(TEXT("twist"), Twist.ToBsonObject());

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("TwistWithCovarianceStamped { header = ") + Header.ToString() +
				TEXT(", twist = ") + Twist.ToString() +
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