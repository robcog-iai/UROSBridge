#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"

namespace geometry_msgs
{
	class Pose : public FROSBridgeMsg
	{
		geometry_msgs::Point Position;
		geometry_msgs::Quaternion Orientation;

	public:
		Pose()
		{
			MsgType = "geometry_msgs/Pose";
		}

		Pose
		(geometry_msgs::Point Inposition, geometry_msgs::Quaternion InOrientation) :
			Position(Inposition), Orientation(InOrientation)
		{
			MsgType = "geometry_msgs/Pose";
		}

		~Pose() override {}

		geometry_msgs::Point GetPosition() const
		{
			return Position;
		}

		geometry_msgs::Quaternion GetOrientation() const
		{
			return Orientation;
		}

		void SetPosition(geometry_msgs::Point InPosition)
		{
			Position = InPosition;
		}

		void SetOrientation(geometry_msgs::Quaternion InOrientation)
		{
			Orientation = InOrientation;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Position = geometry_msgs::Point::GetFromJson(JsonObject->GetObjectField(TEXT("position")));
			Orientation = geometry_msgs::Quaternion::GetFromJson(JsonObject->GetObjectField(TEXT("orientation")));
		}

		static Pose GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Pose Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Pose { position = ") + Position.ToString() +
				TEXT(", orientation = ") + Orientation.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("position"), Position.ToJsonObject());
			Object->SetObjectField(TEXT("orientation"), Orientation.ToJsonObject());
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