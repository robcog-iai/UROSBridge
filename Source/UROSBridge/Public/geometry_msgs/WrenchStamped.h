#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Wrench.h"

namespace geometry_msgs
{
	class WrenchStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Wrench Wrench;

	public:
		WrenchStamped()
		{
			MsgType = "geometry_msgs/WrenchStamped";
		}

		WrenchStamped
		(std_msgs::Header InHeader, geometry_msgs::Wrench InWrench) :
			Header(InHeader), Wrench(InWrench)
		{
			MsgType = "geometry_msgs/WrenchStamped";
		}

		~WrenchStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Wrench GetWrench() const
		{
			return Wrench;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetWrench(geometry_msgs::Wrench InWrench)
		{
			Wrench = InWrench;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Wrench = geometry_msgs::Wrench::GetFromJson(JsonObject->GetObjectField(TEXT("wrench")));
		}

		static WrenchStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			WrenchStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("WrenchStamped { header = ") + Header.ToString() +
				TEXT(", wrench = ") + Wrench.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("wrench"), Wrench.ToJsonObject());
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