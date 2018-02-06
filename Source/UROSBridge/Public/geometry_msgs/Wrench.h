#pragma once
#include "ROSBridgeMsg.h"

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
		(geometry_msgs::Vector3 InForce, geometry_msgs::Vector3 InTorque) :
			Force(InForce), Torque(InTorque)
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

		static Wrench GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Wrench Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Wrench { force = ") + Force.ToString() +
				TEXT(", torque = ") + Torque.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("force"), Force.ToJsonObject());
			Object->SetObjectField(TEXT("torque"), Torque.ToJsonObject());
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