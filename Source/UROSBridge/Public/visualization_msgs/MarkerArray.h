#pragma once

#include "ROSBridgeMsg.h"

#include "visualization_msgs/Marker.h"

class FROSBridgeMsgVisualizationmsgsMarkerArray : public FROSBridgeMsg
{

  TArray<FROSBridgeMsgVisualizationmsgsMarker> markers;

public:
  FROSBridgeMsgVisualizationmsgsMarkerArray()
  {
    MsgType = "visualization_msgs/MarkerArray";
  }

  FROSBridgeMsgVisualizationmsgsMarkerArray
  (const TArray<FROSBridgeMsgVisualizationmsgsMarker> &markers_)
  {
    MsgType = "visualization_msgs/MarkerArray";
    for(int i = 0; i < markers_.Num(); i++)
    {
      markers.Add(markers_[i]);
    }
  }

  ~FROSBridgeMsgVisualizationmsgsMarkerArray() override {}

  TArray<FROSBridgeMsgVisualizationmsgsMarker> GetMarkers() const
  {
    return markers;
  }

  FROSBridgeMsgVisualizationmsgsMarker GetmarkerAt(uint32 Index) const
  {
    check(Index < markers.Num());
    return markers[Index];
  }

  void AddMarker(FROSBridgeMsgVisualizationmsgsMarker marker)
  {
    markers.Add(marker);
  }

  void SetMarkers(const TArray<FROSBridgeMsgVisualizationmsgsMarker>& markers_)
  {
    for (int i = 0; i < markers_.Num(); i++)
    {
        markers.Add(markers_[i]);
    }
  }

  virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
      TArray<TSharedPtr<FJsonValue>> MarkersPtrArray = JsonObject->GetArrayField(TEXT("markers"));
      for (auto &ptr : MarkersPtrArray)
      {
          FROSBridgeMsgVisualizationmsgsMarker marker =
              FROSBridgeMsgVisualizationmsgsMarker::GetFromJson(ptr->AsObject());
          markers.Add(marker);
      }
  }

  static FROSBridgeMsgVisualizationmsgsMarkerArray GetFromJson(TSharedPtr<FJsonObject> JsonObject)
  {
      FROSBridgeMsgVisualizationmsgsMarkerArray Result;
      Result.FromJson(JsonObject);
      return Result;
  }

  virtual FString ToString () const override
  {
      FString ArrayString = "[ ";
      for (auto &marker : markers)
          ArrayString += marker.ToString() + TEXT(", ");
      ArrayString += " ]";

      return TEXT("Markers { marker = ") + ArrayString + TEXT(" } ");
  }

  virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
      TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
      TArray<TSharedPtr<FJsonValue>> MarkersPtrArray;
      for (auto &marker : markers)
      {
          TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(marker.ToJsonObject()));
          MarkersPtrArray.Add(Ptr);
      }

      Object->SetArrayField("markers", MarkersPtrArray);
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
namespace visualization_msgs
{
	class MarkerArray : public FROSBridgeMsg
	{

		TArray<visualization_msgs::Marker> Markers;

	public:
		MarkerArray()
		{
			MsgType = "visualization_msgs/MarkerArray";
		}

		MarkerArray
		(const TArray<visualization_msgs::Marker>& InMarkers)
		{
			MsgType = "visualization_msgs/MarkerArray";
			for (int i = 0; i < InMarkers.Num(); i++)
			{
				Markers.Add(InMarkers[i]);
			}
		}

		~MarkerArray() override {}

		TArray<visualization_msgs::Marker> GetMarkers() const
		{
			return Markers;
		}

		visualization_msgs::Marker GetmarkerAt(uint32 Index) const
		{
			check(Index < Markers.Num());
			return Markers[Index];
		}

		void AddMarker(visualization_msgs::Marker InMarker)
		{
			Markers.Add(InMarker);
		}

		void SetMarkers(const TArray<visualization_msgs::Marker>& InMarkers)
		{
			Markers.Empty();
			Markers = InMarkers;
		}

		void AppendMarkers(const TArray<visualization_msgs::Marker>& InMarkers)
		{
			Markers.Append(InMarkers);
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			TArray<TSharedPtr<FJsonValue>> MarkersPtrArray = JsonObject->GetArrayField(TEXT("markers"));
			for (auto &ptr : MarkersPtrArray)
			{
				visualization_msgs::Marker marker =
					visualization_msgs::Marker::GetFromJson(ptr->AsObject());
				Markers.Add(marker);
			}
		}

		static MarkerArray GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			MarkerArray Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayString = "[ ";
			for (auto &Marker : Markers)
				ArrayString += Marker.ToString() + TEXT(", ");
			ArrayString += " ]";

			return TEXT("Markers { marker = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			TArray<TSharedPtr<FJsonValue>> MarkersPtrArray;
			for (auto &marker : Markers)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(marker.ToJsonObject()));
				MarkersPtrArray.Add(Ptr);
			}

			Object->SetArrayField("markers", MarkersPtrArray);
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
} // namespace visualization_msgs