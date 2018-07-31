#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Vector3.h"

namespace geometry_msgs
{
	class Twist : public FROSBridgeMsg
	{
		geometry_msgs::Vector3 Linear;
		geometry_msgs::Vector3 Angular;
	public:
		Twist()
		{
			MsgType = "geometry_msgs/Twist";
		}

		Twist
		(
			geometry_msgs::Vector3 InLinear,
			geometry_msgs::Vector3 InAngular
		):
			Linear(InLinear),
			Angular(InAngular)
		{
			MsgType = "geometry_msgs/Twist";
		}

		~Twist() override {}

		geometry_msgs::Vector3 GetLinear() const
		{
			return Linear;
		}

		geometry_msgs::Vector3 GetAngular() const
		{
			return Angular;
		}

		void SetLinear(geometry_msgs::Vector3 InLinear)
		{
			Linear = InLinear;
		}

		void SetAngular(geometry_msgs::Vector3 InAngular)
		{
			Angular = InAngular;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Linear = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("linear")));

			Angular = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("angular")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Linear = geometry_msgs::Vector3::GetFromBson(BsonObject->GetObjectField(TEXT("linear")));

			Angular = geometry_msgs::Vector3::GetFromBson(BsonObject->GetObjectField(TEXT("angular")));

		}

		static Twist GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Twist Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Twist GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Twist Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("linear"), Linear.ToJsonObject());
			Object->SetObjectField(TEXT("angular"), Angular.ToJsonObject());
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("linear"), Linear.ToBsonObject());
			Object->SetObjectField(TEXT("angular"), Angular.ToBsonObject());
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