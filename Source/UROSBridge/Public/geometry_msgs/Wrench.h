#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"

class FROSBridgeMsgGeometrymsgsWrench : public FROSBridgeMsg
{
    FROSBridgeMsgGeometrymsgsVector3 force;
    FROSBridgeMsgGeometrymsgsVector3 torque;

public:
    FROSBridgeMsgGeometrymsgsWrench()
    {
        MsgType = "geometry_msgs/Wrench";
    }

    FROSBridgeMsgGeometrymsgsWrench
    (FROSBridgeMsgGeometrymsgsVector3 force_, FROSBridgeMsgGeometrymsgsVector3 torque_) :
        force(force_), torque(torque_)
    {
        MsgType = "geometry_msgs/Wrench";
    }
    
    ~FROSBridgeMsgGeometrymsgsWrench() override {}

    FROSBridgeMsgGeometrymsgsVector3 GetForce() const
    {
        return force; 
    }

    FROSBridgeMsgGeometrymsgsVector3 GetTorque() const
    {
        return torque; 
    }

    void SetForce(FROSBridgeMsgGeometrymsgsVector3 force_)
    {
        force = force_; 
    }

    void SetTorque(FROSBridgeMsgGeometrymsgsVector3 torque_)
    {
        torque = torque_; 
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        force = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("force")));
        torque = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("torque")));
    }

    static FROSBridgeMsgGeometrymsgsWrench GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsWrench Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Wrench { force = ") + force.ToString() + 
                     TEXT(", torque = ") + torque.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("force"), force.ToJsonObject());
        Object->SetObjectField(TEXT("torque"), torque.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
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