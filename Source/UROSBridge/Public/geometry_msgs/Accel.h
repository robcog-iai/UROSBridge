#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"

namespace geometry_msgs
{
	class Accel : public FROSBridgeMsg
	{
		FROSBridgeMsgGeometrymsgsVector3 Linear;
		FROSBridgeMsgGeometrymsgsVector3 Angular;

	public:
		Accel()
		{
			MsgType = "geometry_msgs/Accel";
		}

		Accel
		(FROSBridgeMsgGeometrymsgsVector3 InLinear, FROSBridgeMsgGeometrymsgsVector3 InAngular) :
			Linear(InLinear), Angular(InAngular)
		{
			MsgType = "geometry_msgs/Accel";
		}

		~Accel() override {}

		FROSBridgeMsgGeometrymsgsVector3 GetLinear() const
		{
			return Linear;
		}

		FROSBridgeMsgGeometrymsgsVector3 GetAngular() const
		{
			return Angular;
		}

		void SetLinear(FROSBridgeMsgGeometrymsgsVector3 InLinear)
		{
			Linear = InLinear;
		}

		void SetAngular(FROSBridgeMsgGeometrymsgsVector3 InAngular)
		{
			Angular = InAngular;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Linear = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("linear")));
			Angular = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("angular")));
		}

		static Accel GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Accel Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Accel { linear = ") + Linear.ToString() +
				TEXT(", angular = ") + Angular.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("linear"), Linear.ToJsonObject());
			Object->SetObjectField(TEXT("angular"), Angular.ToJsonObject());
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
