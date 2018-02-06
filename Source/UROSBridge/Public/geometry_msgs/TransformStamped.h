#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Transform.h"

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
			MsgType = "geometry_msgs/TransformStamped";
		}

		TransformStamped(
			std_msgs::Header InHeader,
			FString InChildFrameId,
			geometry_msgs::Transform Transform) :
			Header(InHeader),
			ChildFrameId(InChildFrameId),
			Transform(Transform)
		{
			MsgType = "geometry_msgs/TransformStamped";
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
