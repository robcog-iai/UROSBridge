#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"

class FROSBridgeMsgGeometrymsgsPoseStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsPose pose;

public:
    FROSBridgeMsgGeometrymsgsPoseStamped()
    {
        MsgType = "geometry_msgs/PoseStamped";
    }

    FROSBridgeMsgGeometrymsgsPoseStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsPose pose_) :
        header(header_), pose(pose_)
    {
        MsgType = "geometry_msgs/PoseStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsPoseStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsPose GetPose() const
    {
        return pose; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetPose(FROSBridgeMsgGeometrymsgsPose pose_)
    {
        pose = pose_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        pose = FROSBridgeMsgGeometrymsgsPose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
    }

    static FROSBridgeMsgGeometrymsgsPoseStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPoseStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("PoseStamped { header = ") + header.ToString() + 
                     TEXT(", pose = ") + pose.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("pose"), pose.ToJsonObject());
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
	class PoseStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Pose Pose;

	public:
		PoseStamped()
		{
			MsgType = "geometry_msgs/PoseStamped";
		}

		PoseStamped
		(std_msgs::Header InHeader, geometry_msgs::Pose InPose) :
			Header(InHeader), Pose(InPose)
		{
			MsgType = "geometry_msgs/PoseStamped";
		}

		~PoseStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Pose GetPose() const
		{
			return Pose;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetPose(geometry_msgs::Pose InPose)
		{
			Pose = InPose;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Pose = geometry_msgs::Pose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
		}

		static PoseStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("PoseStamped { header = ") + Header.ToString() +
				TEXT(", pose = ") + Pose.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
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