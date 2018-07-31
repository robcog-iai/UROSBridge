#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/Point32.h"

namespace geometry_msgs
{
	class Polygon : public FROSBridgeMsg
	{
		TArray<geometry_msgs::Point32> Points;
	public:
		Polygon()
		{
			MsgType = "geometry_msgs/Polygon";
		}

		Polygon
		(
			const TArray<geometry_msgs::Point32>& InPoints
		):
			Points(InPoints)
		{
			MsgType = "geometry_msgs/Polygon";
		}

		~Polygon() override {}

		TArray<geometry_msgs::Point32> GetPoints() const
		{
			return Points;
		}

		void SetPoints(TArray<geometry_msgs::Point32>& InPoints)
		{
			Points = InPoints;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Points.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : ValuesPtrArr)
				Points.Add(geometry_msgs::Point32::GetFromJson(ptr->AsObject()));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Points.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : ValuesPtrArr)
				Points.Add(geometry_msgs::Point32::GetFromBson(ptr->AsObject()));

		}

		static Polygon GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Polygon Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Polygon GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Polygon Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> PointsArray;
			for (auto &val : Points)
				PointsArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("points"), PointsArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			TArray<TSharedPtr<FBsonValue>> PointsArray;
			for (auto &val : Points)
				PointsArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("points"), PointsArray);
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
}