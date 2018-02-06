#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Accel.h"

class FROSBridgeMsgGeometrymsgsAccelStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FROSBridgeMsgGeometrymsgsAccel accel;

public:
    FROSBridgeMsgGeometrymsgsAccelStamped()
    {
        MsgType = "geometry_msgs/AccelStamped";
    }

    FROSBridgeMsgGeometrymsgsAccelStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsAccel accel_) :
        header(header_), accel(accel_)
    {
        MsgType = "geometry_msgs/AccelStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsAccelStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsAccel GetAccel() const
    {
        return accel; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetAccel(FROSBridgeMsgGeometrymsgsAccel accel_)
    {
        accel = accel_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        accel = FROSBridgeMsgGeometrymsgsAccel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));
    }

    static FROSBridgeMsgGeometrymsgsAccelStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsAccelStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("AccelStamped { header = ") + header.ToString() + 
                     TEXT(", accel = ") + accel.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("accel"), accel.ToJsonObject());
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
	class AccelStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Accel Accel;

	public:
		AccelStamped()
		{
			MsgType = "geometry_msgs/AccelStamped";
		}

		AccelStamped
		(std_msgs::Header InHeader, geometry_msgs::Accel InAccel) :
			Header(InHeader), Accel(InAccel)
		{
			MsgType = "geometry_msgs/AccelStamped";
		}

		~AccelStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Accel GetAccel() const
		{
			return Accel;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetAccel(geometry_msgs::Accel InAccel)
		{
			Accel = InAccel;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Accel = geometry_msgs::Accel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));
		}

		static AccelStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			AccelStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("AccelStamped { header = ") + Header.ToString() +
				TEXT(", accel = ") + Accel.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("accel"), Accel.ToJsonObject());
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