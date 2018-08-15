#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Inertia.h"


namespace geometry_msgs
{
	class InertiaStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Inertia Inertia;
	public:
		InertiaStamped()
		{
			MsgType = TEXT("geometry_msgs/InertiaStamped");
		}
		
		InertiaStamped(std_msgs::Header InHeader,
			geometry_msgs::Inertia InInertia)
			:
			Header(InHeader),
			Inertia(InInertia)
		{
			MsgType = TEXT("geometry_msgs/InertiaStamped");
		}

		~InertiaStamped() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		geometry_msgs::Inertia GetInertia() const { return Inertia; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetInertia(geometry_msgs::Inertia InInertia) { Inertia = InInertia; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Inertia = geometry_msgs::Inertia::GetFromJson(JsonObject->GetObjectField(TEXT("inertia")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Inertia = geometry_msgs::Inertia::GetFromBson(BsonObject->GetObjectField(TEXT("inertia")));

		}

		static InertiaStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			InertiaStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static InertiaStamped GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			InertiaStamped Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());

			Object->SetObjectField(TEXT("inertia"), Inertia.ToJsonObject());

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());

			Object->SetObjectField(TEXT("inertia"), Inertia.ToBsonObject());

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("InertiaStamped { header = ") + Header.ToString() +
				TEXT(", inertia = ") + Inertia.ToString() +
				TEXT(" } ");

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