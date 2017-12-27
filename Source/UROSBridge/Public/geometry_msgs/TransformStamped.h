#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Transform.h"

class FROSBridgeMsgGeometrymsgsTransformStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header;
    FString child_frame_id; 
    FROSBridgeMsgGeometrymsgsTransform transform;

public:
    FROSBridgeMsgGeometrymsgsTransformStamped()
    {
        Type = "geometry_msgs/TransformStamped";
    }

    FROSBridgeMsgGeometrymsgsTransformStamped
    (FROSBridgeMsgStdmsgsHeader header_, FString child_frame_id_,
     FROSBridgeMsgGeometrymsgsTransform transform_) :
        header(header_), child_frame_id(child_frame_id_), transform(transform_)
    {
        Type = "geometry_msgs/TransformStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsTransformStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FString GetChildFrameId() const 
    {
        return child_frame_id; 
    }

    FROSBridgeMsgGeometrymsgsTransform GetTransform() const
    {
        return transform; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetChildFrameId(FString child_frame_id_)
    {
        child_frame_id = child_frame_id_; 
    }

    void SetTransform(FROSBridgeMsgGeometrymsgsTransform transform_)
    {
        transform = transform_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        child_frame_id = JsonObject->GetStringField(TEXT("child_frame_id")); 
        transform = FROSBridgeMsgGeometrymsgsTransform::GetFromJson(JsonObject->GetObjectField(TEXT("transform")));
    }

    static FROSBridgeMsgGeometrymsgsTransformStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsTransformStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("TransformStamped { header = ") + header.ToString() + 
                     TEXT(", child_frame_id = \"") + child_frame_id + TEXT("\"") + 
                     TEXT(", transform = ") + transform.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetStringField(TEXT("child_frame_id"), child_frame_id);
        Object->SetObjectField(TEXT("transform"), transform.ToJsonObject());
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
	class TransformStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		FString ChildFrameId;
		geometry_msgs::Transform Transform;

	public:
		TransformStamped()
		{
			Type = "geometry_msgs/TransformStamped";
		}

		TransformStamped(
			std_msgs::Header InHeader,
			FString InChildFrameId,
			geometry_msgs::Transform Transform) :
			Header(InHeader),
			ChildFrameId(InChildFrameId),
			Transform(Transform)
		{
			Type = "geometry_msgs/TransformStamped";
		}

		~TransformStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		FString GetChildFrameId() const
		{
			return ChildFrameId;
		}

		geometry_msgs::Transform GetTransform() const
		{
			return Transform;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetChildFrameId(FString InChildFrameId)
		{
			ChildFrameId = InChildFrameId;
		}

		void SetTransform(geometry_msgs::Transform InTransform)
		{
			Transform = InTransform;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			ChildFrameId = JsonObject->GetStringField(TEXT("child_frame_id"));
			Transform = geometry_msgs::Transform::GetFromJson(JsonObject->GetObjectField(TEXT("transform")));
		}

		static TransformStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TransformStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("TransformStamped { header = ") + Header.ToString() +
				TEXT(", child_frame_id = \"") + ChildFrameId + TEXT("\"") +
				TEXT(", transform = ") + Transform.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetStringField(TEXT("child_frame_id"), ChildFrameId);
			Object->SetObjectField(TEXT("transform"), Transform.ToJsonObject());
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
