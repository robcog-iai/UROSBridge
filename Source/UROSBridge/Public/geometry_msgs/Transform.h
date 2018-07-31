#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"

namespace geometry_msgs
{
	class Transform : public FROSBridgeMsg
	{
		geometry_msgs::Vector3 Translation;
		geometry_msgs::Quaternion Rotation;
	public:
		Transform()
		{
			MsgType = "geometry_msgs/Transform";
		}

		Transform
		(
			geometry_msgs::Vector3 InTranslation,
			geometry_msgs::Quaternion InRotation
		):
			Translation(InTranslation),
			Rotation(InRotation)
		{
			MsgType = "geometry_msgs/Transform";
		}

		~Transform() override {}

		geometry_msgs::Vector3 GetTranslation() const
		{
			return Translation;
		}

		geometry_msgs::Quaternion GetRotation() const
		{
			return Rotation;
		}

		void SetTranslation(geometry_msgs::Vector3 InTranslation)
		{
			Translation = InTranslation;
		}

		void SetRotation(geometry_msgs::Quaternion InRotation)
		{
			Rotation = InRotation;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Translation = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("translation")));

			Rotation = geometry_msgs::Quaternion::GetFromJson(JsonObject->GetObjectField(TEXT("rotation")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Translation = geometry_msgs::Vector3::GetFromBson(BsonObject->GetObjectField(TEXT("translation")));

			Rotation = geometry_msgs::Quaternion::GetFromBson(BsonObject->GetObjectField(TEXT("rotation")));

		}

		static Transform GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Transform Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Transform GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Transform Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("translation"), Translation.ToJsonObject());
			Object->SetObjectField(TEXT("rotation"), Rotation.ToJsonObject());
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("translation"), Translation.ToBsonObject());
			Object->SetObjectField(TEXT("rotation"), Rotation.ToBsonObject());
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