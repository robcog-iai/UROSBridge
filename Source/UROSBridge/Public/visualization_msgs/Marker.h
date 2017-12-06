#pragma once

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
                   } type;

  enum action_type {ADD = 0,
                    MODIFY = 0,
                    DELETE = 2
                   } action;

  FROSBridgeMsgStdmsgsHeader header;
  FString ns;
  int32 id;

  FROSBridgeMsgGeometrymsgsPose pose;
  FROSBridgeMsgGeometrymsgsVector3 scale;
  FROSBridgeMsgStdmsgsColorRGBA color;
  uint32 lifetime;
  bool frame_locked;

  TArray<FROSBridgeMsgGeometrymsgsPoint> points;
  TArray<FROSBridgeMsgStdmsgsColorRGBA> colors;
  FString text;

  FString mesh_resource;
  bool mesh_use_embedded_materials;

public:
  FROSBridgeMsgVisualizationmsgsMarker()
  {
    Type = "visualization_msgs/Marker";
  }

  //check what is the minimum requirement for a marker
  FROSBridgeMsgVisualizationmsgsMarker(FROSBridgeMsgStdmsgsHeader header_, FString ns_,
                                       marker_type type_,  action_type action_,
                                       FROSBridgeMsgGeometrymsgsPose pose_, FROSBridgeMsgGeometrymsgsVector3 scale_,
                                       FROSBridgeMsgStdmsgsColorRGBA color_, uint32 lifetime_,
                                       bool frame_locked_):
    type(type_), action(action_), header(header_), ns(ns_), pose(pose_.GetPosition(), pose_.GetOrientation()),
    scale(scale_.GetVector()),
    color(color_.GetColor()), lifetime(lifetime_), frame_locked(frame_locked_)
  {
    Type = "visualization_msgs/Marker";
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

  int32 GetId() const
  {
    return id;
  }

  int GetMarkeType() const
  {
    return type;
  }

  int GetActionTye() const
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

  FROSBridgeMsgStdmsgsColorRGBA GetColor() const
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
  TArray<FROSBridgeMsgStdmsgsColorRGBA> GetColors() const
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

  virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
  {

    header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
    ns = JsonObject->GetStringField(TEXT("ns"));
    id = JsonObject->GetIntegerField(TEXT("id"));
    type = (marker_type)JsonObject->GetIntegerField(TEXT("type"));
    action = (action_type)JsonObject->GetIntegerField(TEXT("action"));
    pose = FROSBridgeMsgGeometrymsgsPose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
    scale = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("scale")));
    color = FROSBridgeMsgStdmsgsColorRGBA::GetFromJson(JsonObject->GetObjectField(TEXT("color")));

    TSharedPtr<FJsonObject> lifeTimeObj = JsonObject->GetObjectField("lifetime");
    lifetime = lifeTimeObj->GetIntegerField("secs");
    frame_locked = JsonObject->GetBoolField(TEXT("frame_locked"));

    TArray<TSharedPtr<FJsonValue>> ValuesPtrArray = JsonObject->GetArrayField(TEXT("points"));
    for(auto & ptr : ValuesPtrArray)
    {
      FROSBridgeMsgGeometrymsgsPoint point = FROSBridgeMsgGeometrymsgsPoint::GetFromJson(ptr->AsObject());
      points.Add(point);
    }

    ValuesPtrArray = JsonObject->GetArrayField(TEXT("colors"));
    for(auto & ptr : ValuesPtrArray)
    {
      FROSBridgeMsgStdmsgsColorRGBA c = FROSBridgeMsgStdmsgsColorRGBA::GetFromJson(ptr->AsObject());
      colors.Add(c);
    }

    text = JsonObject->GetStringField(TEXT("text"));
    mesh_resource = JsonObject->GetStringField(TEXT("mesh_resource"));
    mesh_use_embedded_materials = JsonObject->GetBoolField(TEXT("mesh_use_embedded_materials"));
  }

  static FROSBridgeMsgVisualizationmsgsMarker GetFromJson(TSharedPtr<FJsonObject> JsonObject)
  {
    FROSBridgeMsgVisualizationmsgsMarker Result;
    Result.FromJson(JsonObject);
    return Result;
  }

  virtual FString ToString() const override
  {
    /*
     * TODO:IMPLEMENT
     * */
    return TEXT("Marker { header = ") + header.ToString();
  }

  virtual TSharedPtr<FJsonObject> ToJsonObject() const override
  {
    TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
    Object->SetObjectField(TEXT("header"), header.ToJsonObject());
    Object->SetStringField(TEXT("ns"), ns);
    Object->SetNumberField(TEXT("id"), id);
    Object->SetNumberField(TEXT("type"), type);
    Object->SetNumberField(TEXT("action"), action);
    Object->SetObjectField(TEXT("pose"), pose.ToJsonObject());
    Object->SetObjectField(TEXT("scale"), scale.ToJsonObject());
    Object->SetObjectField(TEXT("color"), color.ToJsonObject());

    TSharedPtr<FJsonObject> lifetime_ = MakeShareable<FJsonObject>(new FJsonObject());
    lifetime_->SetNumberField(TEXT("secs"),lifetime);
    lifetime_->SetNumberField(TEXT("nsecs"),0.0);
    Object->SetObjectField(TEXT("lifetime"), lifetime_);

    Object->SetBoolField(TEXT("frame_locked"), frame_locked);

    TArray<TSharedPtr<FJsonValue>> PointsPtrArray;
    for(auto & point : points)
    {
      TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(point.ToJsonObject()));
      PointsPtrArray.Add(Ptr);
    }
    Object->SetArrayField(TEXT("points"), PointsPtrArray);

    TArray<TSharedPtr<FJsonValue>> ColorsPtrArray;
    for(auto & c : colors)
    {
      TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(c.ToJsonObject()));
      ColorsPtrArray.Add(Ptr);
    }
    Object->SetArrayField(TEXT("colors"), ColorsPtrArray);

    Object->SetStringField(TEXT("text"), text);
    Object->SetStringField(TEXT("mesh_resource"), mesh_resource);
    Object->SetBoolField(TEXT("mesh_use_embedded_materials"), mesh_use_embedded_materials);

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
