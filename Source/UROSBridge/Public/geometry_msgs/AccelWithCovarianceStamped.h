#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/AccelWithCovariance.h"

namespace geometry_msgs
{
	class AccelWithCovarianceStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::AccelWithCovariance Accel;
	public:
		AccelWithCovarianceStamped()
		{
			MsgType = "geometry_msgs/AccelWithCovarianceStamped";
		}

		AccelWithCovarianceStamped
		(
			std_msgs::Header InHeader,
			geometry_msgs::AccelWithCovariance InAccel
		):
			Header(InHeader),
			Accel(InAccel)
		{
			MsgType = "geometry_msgs/AccelWithCovarianceStamped";
		}

		~AccelWithCovarianceStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::AccelWithCovariance GetAccel() const
		{
			return Accel;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetAccel(geometry_msgs::AccelWithCovariance InAccel)
		{
			Accel = InAccel;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Accel = geometry_msgs::AccelWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Accel = geometry_msgs::AccelWithCovariance::GetFromBson(BsonObject->GetObjectField(TEXT("accel")));

		}

		static AccelWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			AccelWithCovarianceStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static AccelWithCovarianceStamped GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			AccelWithCovarianceStamped Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("accel"), Accel.ToJsonObject());
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());
			Object->SetObjectField(TEXT("accel"), Accel.ToBsonObject());
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