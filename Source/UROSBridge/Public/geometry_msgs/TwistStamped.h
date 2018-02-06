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
		(std_msgs::Header InHeader, geometry_msgs::Twist InTwist) :
			Header(InHeader), Twist(InTwist)
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

		static TwistStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TwistStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("TwistStamped { header = ") + Header.ToString() +
				TEXT(", twist = ") + Twist.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("twist"), Twist.ToJsonObject());
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