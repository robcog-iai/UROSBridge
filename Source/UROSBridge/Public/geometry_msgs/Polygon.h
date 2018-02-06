#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Point32.h"

namespace geometry_msgs
{
	class Polygon : public FROSBridgeMsg
	{
	public:
		TArray<geometry_msgs::Point32> Points;

		Polygon()
		{
			MsgType = "geometry_msgs/Polygon";
		}

		Polygon
		(const TArray<geometry_msgs::Point32>& InPoints)
		{
			MsgType = "geometry_msgs/Polygon";
			Points = InPoints;
		}

		~Polygon() override {}

		TArray<geometry_msgs::Point32> GetPoints() const
		{
			return Points;
		}

		geometry_msgs::Point32 GetPointAt(uint32 Index)
		{
			check(Index < Points.Num());
			return Points[Index];
		}

		void AddPoint(geometry_msgs::Point32 point)
		{
			Points.Add(point);
		}

		void SetPoints(const TArray<geometry_msgs::Point32>& InPoints)
		{
			Points.Empty();
			Points = InPoints;
		}

		void AppendPoints(const TArray<geometry_msgs::Point32>& InPoints)
		{
			Points.Append(InPoints);
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			TArray<TSharedPtr<FJsonValue>> PointsPtrArray = JsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : PointsPtrArray)
			{
				geometry_msgs::Point32 point =
					geometry_msgs::Point32::GetFromJson(ptr->AsObject());
				Points.Add(point);
			}
		}

		static Polygon GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Polygon Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayString = "[ ";
			for (auto &point : Points)
				ArrayString += point.ToString() + TEXT(", ");
			ArrayString += " ]";

			return TEXT("Polygon { points = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			TArray<TSharedPtr<FJsonValue>> PointsPtrArray;
			for (auto &point : Points)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(point.ToJsonObject()));
				PointsPtrArray.Add(Ptr);
			}

			Object->SetArrayField("points", PointsPtrArray);
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