#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/AccelWithCovariance.h"

namespace geometry_msgs
{
	class AccelWithCovarianceStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::AccelWithCovariance AccelWithCovariance;

	public:
		AccelWithCovarianceStamped()
		{
			MsgType = "geometry_msgs/AccelWithCovarianceStamped";
		}

		AccelWithCovarianceStamped
		(std_msgs::Header InHeader, geometry_msgs::AccelWithCovariance InAccelWithCovariance) :
			Header(InHeader), AccelWithCovariance(InAccelWithCovariance)
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
			return AccelWithCovariance;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetAccel(geometry_msgs::AccelWithCovariance InAccelWithCovariance)
		{
			AccelWithCovariance = InAccelWithCovariance;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			AccelWithCovariance = geometry_msgs::AccelWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));
		}

		static AccelWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			AccelWithCovarianceStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("AccelWithCovarianceStamped { header = ") + Header.ToString() +
				TEXT(", accel = ") + AccelWithCovariance.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("accel"), AccelWithCovariance.ToJsonObject());
			return Object;
		}

		virtual FString ToYamlString() const override {
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
} // namespace geometry_msgs