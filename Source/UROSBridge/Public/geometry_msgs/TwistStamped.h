#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Twist.h"

namespace geometry_msgs
{
	class TwistStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Twist Twist;
	public:
		TwistStamped()
		{
			MsgType = "geometry_msgs/TwistStamped";
		}

		TwistStamped
		(
			std_msgs::Header InHeader,
			geometry_msgs::Twist InTwist
		):
			Header(InHeader),
			Twist(InTwist)
		{
			MsgType = "geometry_msgs/TwistStamped";
		}

		~TwistStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Twist GetTwist() const
		{
			return Twist;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetTwist(geometry_msgs::Twist InTwist)
		{
			Twist = InTwist;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Twist = geometry_msgs::Twist::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Twist = geometry_msgs::Twist::GetFromBson(BsonObject->GetObjectField(TEXT("twist")));

		}

		static TwistStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TwistStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static TwistStamped GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			TwistStamped Result;
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
		virtual FString ToYamlString() const override
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
}