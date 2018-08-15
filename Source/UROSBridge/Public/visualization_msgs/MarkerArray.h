#pragma once

#include "ROSBridgeMsg.h"
#include "visualization_msgs/Marker.h"


namespace visualization_msgs
{
	class MarkerArray : public FROSBridgeMsg
	{
		TArray<visualization_msgs::Marker> Markers;
	public:
		MarkerArray()
		{
			MsgType = TEXT("visualization_msgs/MarkerArray");
		}
		
		MarkerArray(TArray<visualization_msgs::Marker> InMarkers)
			:
			Markers(InMarkers)
		{
			MsgType = TEXT("visualization_msgs/MarkerArray");
		}

		~MarkerArray() override {}

		// Getters 
		TArray<visualization_msgs::Marker> GetMarkers() const { return Markers; }

		// DEPRECATED! Will be removed when the generator is used again.
		visualization_msgs::Marker GetmarkerAt(int32 Index) const
		{
			check(Index < Markers.Num());
			return Markers[Index];
		}

		// Setters 
		void SetMarkers(TArray<visualization_msgs::Marker> InMarkers) { Markers = InMarkers; }

		// DEPRECATED! Will be removed when the generator is used again.
		void AddMarker(visualization_msgs::Marker InMarker)
		{
			Markers.Add(InMarker);
		}
		
		// DEPRECATED! Will be removed when the generator is used again.
		void AppendMarkers(const TArray<visualization_msgs::Marker>& InMarkers)
		{
			Markers.Append(InMarkers);
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Markers.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("markers"));
			for (auto &ptr : ValuesPtrArr)
				Markers.Add(visualization_msgs::Marker::GetFromJson(ptr->AsObject()));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Markers.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("markers"));
			for (auto &ptr : ValuesPtrArr)
				Markers.Add(visualization_msgs::Marker::GetFromBson(ptr->AsObject()));

		}

		static MarkerArray GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			MarkerArray Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static MarkerArray GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			MarkerArray Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> MarkersArray;
			for (auto &val : Markers)
				MarkersArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("markers"), MarkersArray);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			TArray<TSharedPtr<FBsonValue>> MarkersArray;
			for (auto &val : Markers)
				MarkersArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("markers"), MarkersArray);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			FString MarkersString = "[ ";
			for (auto &value : Markers)
				MarkersString += value.ToString() + TEXT(", ");
			MarkersString += " ] ";
			return TEXT("MarkerArray { markers =") + MarkersString +
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