#pragma once

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
    Type = "visualization_msgs/MarkerArray";
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
        markers.Add(markers_[i]);
    }
  }

  virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
      TArray<TSharedPtr<FJsonValue>> MarkersPtrArray = JsonObject->GetArrayField(TEXT("merkers"));
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
