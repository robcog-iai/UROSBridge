#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace geometry_msgs
{
	class Vector3Stamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Vector3 Vector;

	public:
		Vector3Stamped()
		{
			MsgType = "geometry_msgs/Vector3Stamped";
		}

		Vector3Stamped
		(std_msgs::Header InHeader, geometry_msgs::Vector3 InVector) :
			Header(InHeader), Vector(InVector)
		{
			MsgType = "geometry_msgs/Vector3Stamped";
		}

		~Vector3Stamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Vector3 GetVector() const
		{
			return Vector;
		}

		void SetHeader(std_msgs::Header header_)
		{
			Header = header_;
		}

		void SetVector(geometry_msgs::Vector3 vector_)
		{
			Vector = vector_;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Vector = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("vector")));
		}

		static Vector3Stamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Vector3Stamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Vector3Stamped { header = ") + Header.ToString() +
				TEXT(", vector = ") + Vector.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("vector"), Vector.ToJsonObject());
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