#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Polygon.h"


namespace geometry_msgs
{
	class PolygonStamped : public FROSBridgeMsg
	{
		std_msgs::Header Header;
		geometry_msgs::Polygon Polygon;
	public:
		PolygonStamped()
		{
			MsgType = TEXT("geometry_msgs/PolygonStamped");
		}
		
		PolygonStamped(std_msgs::Header InHeader,
			geometry_msgs::Polygon InPolygon)
			:
			Header(InHeader),
			Polygon(InPolygon)
		{
			MsgType = TEXT("geometry_msgs/PolygonStamped");
		}

		~PolygonStamped() override {}

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		geometry_msgs::Polygon GetPolygon() const { return Polygon; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetPolygon(geometry_msgs::Polygon InPolygon) { Polygon = InPolygon; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Polygon = geometry_msgs::Polygon::GetFromJson(JsonObject->GetObjectField(TEXT("polygon")));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Polygon = geometry_msgs::Polygon::GetFromBson(BsonObject->GetObjectField(TEXT("polygon")));

		}

		static PolygonStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PolygonStamped Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static PolygonStamped GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			PolygonStamped Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());

			Object->SetObjectField(TEXT("polygon"), Polygon.ToJsonObject());

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());

			Object->SetObjectField(TEXT("polygon"), Polygon.ToBsonObject());

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("PolygonStamped { header = ") + Header.ToString() +
				TEXT(", polygon = ") + Polygon.ToString() +
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