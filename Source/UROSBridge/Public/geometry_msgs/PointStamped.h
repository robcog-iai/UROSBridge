#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Point.h"

namespace geometry_msgs
{
	class PointStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Point Point;

	public:
		PointStamped()
		{
			MsgType = "geometry_msgs/PointStamped";
		}

		PointStamped
		(std_msgs::Header InHeader, geometry_msgs::Point InPoint) :
			Header(InHeader), Point(InPoint)
		{
			MsgType = "geometry_msgs/PointStamped";
		}

		~PointStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Point GetPoint() const
		{
			return Point;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetPoint(geometry_msgs::Point InPoint)
		{
			Point = InPoint;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Point = geometry_msgs::Point::GetFromJson(JsonObject->GetObjectField(TEXT("point")));
		}

		static PointStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PointStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("PointStamped { header = ") + Header.ToString() +
				TEXT(", point = ") + Point.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("point"), Point.ToJsonObject());
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