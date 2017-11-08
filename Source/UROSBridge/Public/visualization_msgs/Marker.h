#ifndef MARKER_H
#define MARKER_H

#include "ROSBridgeMsg.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/Header.h"
#include "std_msgs/ColorRGBA.h"

class FROSBridgeMsgVisualizationmsgsMarker : public FROSBridgeMsg
{

  enum marker_type {ARROW = 0,
                    CUBE, SPHERE, CYLINDER, LINE_STRIP,
                    LINE_LIST, CUBE_LIST, SPHERE_LIST,
                    POINTS, TEXT_VIEW_FACING, MESH_RESOURCE, TRIANGLE_LIST
                   };

  enum action_type {ADD = 0, MODIFY = 0, DELETE = 2};

  FROSBridgeMsgStdmsgsHeader header;
  FString ns;
  int32 id;
  marker_type type;
  action_type action;
  FROSBridgeMsgGeometrymsgsPose pose;
  FROSBridgeMsgGeometrymsgsVector3 scale;
  TArray<float, TFixedAllocator<4>> color;
  uint32 lifetime;
  bool frame_locked;

  TArray<FROSBridgeMsgGeometrymsgsPoint> points;
  TArray<float> colors;
  FString text;

  FString mesh_resource;
  bool mesh_use_embedded_materials;

  FROSBridgeMsgVisualizationmsgsMarker()
  {
    type = "visualization_msgs/Marker";
  }

  //check what is the minimum requirement for a marker
  FROSBridgeMsgVisualizationmsgsMarker(FROSBridgeMsgStdmsgsHeader header_, FString ns_,
                                       marker_type type_,  action_type action_,
                                       FROSBridgeMsgGeometrymsgsPose pose_, FROSBridgeMsgGeometrymsgsVector3 scale_,
                                       TArray<float, TFixedAllocator<4>> color_, uint32 lifetime_,
                                       bool frame_locked_):
    header(header_), ns(ns_), type(type_), action(action_), pose(pose_), scale(scale_),
    color(color_), lifetime(lifetime_), frame_locked(frame_locked_)
  {
    type = "visualization_msgs/Marker";
  }

  //getters
  FROSBridgeMsgStdmsgsHeader GetHeader() const
  {
    return header;
  }

  FString GetNamespace() const
  {
    return ns;
  }

  int GetMarkeType() const
  {
    return type;
  }

  int GetActiontupe() const
  {
    return action;
  }

  FROSBridgeMsgGeometrymsgsPose GetPose() const
  {
    return pose;
  }

  FROSBridgeMsgGeometrymsgsVector3 GetScale() const
  {
    return scale;
  }

  TArray<float, TFixedAllocator<4>> GetColor() const
  {
    return color;
  }

  uint32 GetDuration() const
  {
    return lifetime;
  }

  bool GetFrameLocked() const
  {
    return frame_locked;
  }

  TArray<FROSBridgeMsgGeometrymsgsPoint> GetPoints() const
  {
    return points;
  }
  TArray<float> GetColors() const
  {
    return colors;
  }

  FString GetMeshResource() const
  {
    return mesh_resource;
  }

  FString GetText() const
  {
    return text;
  }

  //Setters
  /*
   * TODO: Implemente the setters for this ros message
   * */

  virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
      header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
      ns = JsonObject->GetStringField(TEXT("ns"));
      id =
      pose = FROSBridgeMsgGeometrymsgsPose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));

//      child_frame_id = JsonObject->GetStringField(TEXT("child_frame_id"));
//      transform = FROSBridgeMsgGeometrymsgsTransform::GetFromJson(JsonObject->GetObjectField(TEXT("transform")));
  }

  static FROSBridgeMsgVisualizationmsgsMarker GetFromJson(TSharedPtr<FJsonObject> JsonObject)
  {
    FROSBridgeMsgVisualizationmsgsMarker Result;
    Result.FromJson(JsonObject);
    return Result;
  }

  virtual FString ToString() const override
  {
    return TEXT("Marker { header = ") + header.ToString();
  }

  virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
      TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
      Object->SetObjectField(TEXT("header"), header.ToJsonObject());
      return Object;
  }

  virtual FString ToYamlString() const override {
      FString OutputString;
      TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
      FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
      return OutputString;
  }


};
#endif // MARKER_H
