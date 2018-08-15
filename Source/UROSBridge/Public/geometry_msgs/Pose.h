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
			MsgType = TEXT("geometry_msgs/Pose");
		}
		
		Pose(geometry_msgs::Point InPosition,
			geometry_msgs::Quaternion InOrientation)
			:
			Position(InPosition),
			Orientation(InOrientation)
		{
			MsgType = TEXT("geometry_msgs/Pose");
		}

		~Pose() override {}

		// Getters 
		geometry_msgs::Point GetPosition() const { return Position; }
		geometry_msgs::Quaternion GetOrientation() const { return Orientation; }

		// Setters 
		void SetPosition(geometry_msgs::Point InPosition) { Position = InPosition; }
		void SetOrientation(geometry_msgs::Quaternion InOrientation) { Orientation = InOrientation; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Position = geometry_msgs::Point::GetFromJson(JsonObject->GetObjectField(TEXT("position")));

			Orientation = geometry_msgs::Quaternion::GetFromJson(JsonObject->GetObjectField(TEXT("orientation")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Position = geometry_msgs::Point::GetFromBson(BsonObject->GetObjectField(TEXT("position")));

			Orientation = geometry_msgs::Quaternion::GetFromBson(BsonObject->GetObjectField(TEXT("orientation")));

		}

		static Pose GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Pose Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Pose GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Pose Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("position"), Position.ToJsonObject());

			Object->SetObjectField(TEXT("orientation"), Orientation.ToJsonObject());

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("position"), Position.ToBsonObject());

			Object->SetObjectField(TEXT("orientation"), Orientation.ToBsonObject());

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("Pose { position = ") + Position.ToString() +
				TEXT(", orientation = ") + Orientation.ToString() +
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