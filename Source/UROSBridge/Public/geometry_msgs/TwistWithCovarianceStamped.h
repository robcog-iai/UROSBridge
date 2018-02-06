#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/TwistWithCovariance.h"

class FROSBridgeMsgGeometrymsgsTwistWithCovarianceStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsTwistWithCovariance twist;

public:
    FROSBridgeMsgGeometrymsgsTwistWithCovarianceStamped()
    {
        MsgType = "geometry_msgs/TwistWithCovarianceStamped";
    }

    FROSBridgeMsgGeometrymsgsTwistWithCovarianceStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsTwistWithCovariance twist_) :
        header(header_), twist(twist_)
    {
        MsgType = "geometry_msgs/TwistWithCovarianceStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsTwistWithCovarianceStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsTwistWithCovariance GetTwist() const
    {
        return twist; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetTwist(FROSBridgeMsgGeometrymsgsTwistWithCovariance twist_)
    {
        twist = twist_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        twist = FROSBridgeMsgGeometrymsgsTwistWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));
    }

    static FROSBridgeMsgGeometrymsgsTwistWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsTwistWithCovarianceStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("TwistWithCovarianceStamped { header = ") + header.ToString() + 
                     TEXT(", twist = ") + twist.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("twist"), twist.ToJsonObject());
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
	class TwistWithCovarianceStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::TwistWithCovariance Twist;

	public:
		TwistWithCovarianceStamped()
		{
			MsgType = "geometry_msgs/TwistWithCovarianceStamped";
		}

		TwistWithCovarianceStamped
		(std_msgs::Header InHeader, geometry_msgs::TwistWithCovariance InTwist) :
			Header(InHeader), Twist(InTwist)
		{
			MsgType = "geometry_msgs/TwistWithCovarianceStamped";
		}

		~TwistWithCovarianceStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::TwistWithCovariance GetTwist() const
		{
			return Twist;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetTwist(geometry_msgs::TwistWithCovariance InTwist)
		{
			Twist = InTwist;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Twist = geometry_msgs::TwistWithCovariance::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));
		}

		static TwistWithCovarianceStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TwistWithCovarianceStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("TwistWithCovarianceStamped { header = ") + Header.ToString() +
				TEXT(", twist = ") + Twist.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("twist"), Twist.ToJsonObject());
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