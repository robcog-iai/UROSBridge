#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Accel.h"

namespace geometry_msgs
{
	class AccelStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Accel Accel;

	public:
		AccelStamped()
		{
			MsgType = "geometry_msgs/AccelStamped";
		}

		AccelStamped
		(std_msgs::Header InHeader, geometry_msgs::Accel InAccel) :
			Header(InHeader), Accel(InAccel)
		{
			MsgType = "geometry_msgs/AccelStamped";
		}

		~AccelStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Accel GetAccel() const
		{
			return Accel;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetAccel(geometry_msgs::Accel InAccel)
		{
			Accel = InAccel;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Accel = geometry_msgs::Accel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));
		}

		static AccelStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			AccelStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("AccelStamped { header = ") + Header.ToString() +
				TEXT(", accel = ") + Accel.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("accel"), Accel.ToJsonObject());
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