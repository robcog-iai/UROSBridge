#ifndef MARKERARRAY_H
#define MARKERARRAY_H

#endif // MARKERARRAY_H

#include "ROSBridgeMsg.h"
#include "visualization_msgs/Marker.h"

class FROSBridgeMsgVisualizationmsgsMarkerArray : public FROSBridgeMsg
{

  TArray<FROSBridgeMsgVisualizationmsgsMarker> markers;


  FROSBridgeMsgVisualizationmsgsMarkerArray()
  {
    Type = "visualization_msgs/MarkerArray";
  }

  FROSBridgeMsgVisualizationmsgsMarkerArray
  (const TArray<FROSBridgeMsgVisualizationmsgsMarker> &markers_)
  {
    Type = "geometry_msgs/Polygon";
    for(int i = 0; i < points_.Num(); i++)
    {
      markers.Add(points_[i]);
    }
  }

  ~FROSBridgeMsgVisualizationmsgsMarkerArray() override {}

  TArray<FROSBridgeMsgVisualizationmsgsMarker> GetMarkers() const
  {
    return markers;
  }

  FROSBridgeMsgVisualizationmsgsMarker getmarkerAt(uint32 Index) const
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
        markers.Add(points_[i]);
    }
  }

  virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
      TArray<TSharedPtr<FJsonValue>> PointsPtrArray = JsonObject->GetArrayField(TEXT("points"));
      for (auto &ptr : PointsPtrArray)
      {
          FROSBridgeMsgGeometrymsgsPoint32 point =
              FROSBridgeMsgGeometrymsgsPoint32::GetFromJson(ptr->AsObject());
          points.Add(point);
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
