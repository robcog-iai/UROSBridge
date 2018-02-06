#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Quaternion.h"

namespace geometry_msgs
{
	class QuaternionStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Quaternion Quaternion;

	public:
		QuaternionStamped()
		{
			MsgType = "geometry_msgs/QuaternionStamped";
		}

		QuaternionStamped
		(std_msgs::Header InHeader, geometry_msgs::Quaternion InQuaternion) :
			Header(InHeader), Quaternion(InQuaternion)
		{
			MsgType = "geometry_msgs/QuaternionStamped";
		}

		~QuaternionStamped() override {}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		geometry_msgs::Quaternion GetQuaternion() const
		{
			return Quaternion;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetQuaternion(geometry_msgs::Quaternion InQuaternion)
		{
			Quaternion = InQuaternion;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Quaternion = geometry_msgs::Quaternion::GetFromJson(JsonObject->GetObjectField(TEXT("quaternion")));
		}

		static QuaternionStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			QuaternionStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("QuaternionStamped { header = ") + Header.ToString() +
				TEXT(", quaternion = ") + Quaternion.ToString() + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetObjectField(TEXT("quaternion"), Quaternion.ToJsonObject());
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