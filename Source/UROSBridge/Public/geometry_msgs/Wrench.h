#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Vector3.h"

namespace geometry_msgs
{
	class Wrench : public FROSBridgeMsg
	{
		geometry_msgs::Vector3 Force;
		geometry_msgs::Vector3 Torque;
	public:
		Wrench()
		{
			MsgType = "geometry_msgs/Wrench";
		}

		Wrench
		(
			geometry_msgs::Vector3 InForce,
			geometry_msgs::Vector3 InTorque
		):
			Force(InForce),
			Torque(InTorque)
		{
			MsgType = "geometry_msgs/Wrench";
		}

		~Wrench() override {}

		geometry_msgs::Vector3 GetForce() const
		{
			return Force;
		}

		geometry_msgs::Vector3 GetTorque() const
		{
			return Torque;
		}

		void SetForce(geometry_msgs::Vector3 InForce)
		{
			Force = InForce;
		}

		void SetTorque(geometry_msgs::Vector3 InTorque)
		{
			Torque = InTorque;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Force = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("force")));

			Torque = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("torque")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Force = geometry_msgs::Vector3::GetFromBson(BsonObject->GetObjectField(TEXT("force")));

			Torque = geometry_msgs::Vector3::GetFromBson(BsonObject->GetObjectField(TEXT("torque")));

		}

		static Wrench GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Wrench Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Wrench GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Wrench Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("force"), Force.ToJsonObject());
			Object->SetObjectField(TEXT("torque"), Torque.ToJsonObject());
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("force"), Force.ToBsonObject());
			Object->SetObjectField(TEXT("torque"), Torque.ToBsonObject());
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