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
    MsgType = "visualization_msgs/Marker";
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
    MsgType = "visualization_msgs/Marker";
  }

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

  marker_type GetMarkeType() const
  {
    return type;
  }

  action_type GetActionTye() const
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

  // Setters
  void SetHeader(FROSBridgeMsgStdmsgsHeader _header)
  {
	header = _header;
  }

  void SetNamespace(FString _ns)
  {
	ns = _ns;
  }

  void SetId(int32 _id)
  {
	id = _id;
  }

  void SetMarkeType(marker_type _type)
  {
	type = _type;
  }

  void SetActionTye(action_type _action)
  {
	action = _action;
  }

  void SetPose(FROSBridgeMsgGeometrymsgsPose _pose)
  {
    pose = _pose;
  }

  void SetScale(FROSBridgeMsgGeometrymsgsVector3 _scale)
  {
    scale = _scale;
  }

  void SetColor(FROSBridgeMsgStdmsgsColorRGBA _color)
  {
	color = _color;
  }

  void SetDuration(uint32 _lifetime)
  {
	lifetime = _lifetime;
  }

  void SetFrameLocked(bool _frame_locked)
  {
	frame_locked = _frame_locked;
  }

  void SetPoints(TArray<FROSBridgeMsgGeometrymsgsPoint> _points)
  {
	  points = _points;
  }
  void SetColors(TArray<FROSBridgeMsgStdmsgsColorRGBA> _colors)
  {
	  colors = _colors;
  }

  void SetMeshResource(FString _mesh_resource)
  {
	mesh_resource = _mesh_resource;
  }

  void SetText(FString _text)
  {
	  text = _text;
  }

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

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
namespace visualization_msgs
{
	class Marker : public FROSBridgeMsg
	{
		enum EType : uint8
		{
			ARROW = 0,
			CUBE = 1,
			SPHERE = 2,
			CYLINDER = 3,
			LINE_STRIP = 4,
			LINE_LIST = 5,
			CUBE_LIST = 6,
			SPHERE_LIST = 7,
			POINTS = 8,
			TEXT_VIEW_FACING = 9,
			MESH_RESOURCE = 10,
			TRIANGLE_LIST = 11
		};

		enum EAction : uint8
		{
			ADD = 0,
			MODIFY = 0,
			DELETE = 2
		};

		std_msgs::Header Header;
		FString Ns;
		int32 Id;
		EType Type;
		EAction Action;
		geometry_msgs::Pose Pose;
		geometry_msgs::Vector3 Scale;
		std_msgs::ColorRGBA Color;
		uint32 Lifetime;
		bool bFrameLocked;
		TArray<geometry_msgs::Point> Points;
		TArray<std_msgs::ColorRGBA> Colors;
		FString Text;
		FString MeshResource;
		bool bMeshUseEmbeddedMaterials;

	public:
		Marker()
		{
			MsgType = "visualization_msgs/Marker";
		}

		//check what is the minimum requirement for a marker
		Marker(std_msgs::Header InHeader, FString InNs,
			EType InMarkerType, EAction InActionType,
			geometry_msgs::Pose InPose, geometry_msgs::Vector3 InScale,
			std_msgs::ColorRGBA InColor, uint32 InLifetime,
			bool bInFrameLocked) :
			Type(InMarkerType), Action(InActionType), Header(InHeader), Ns(InNs), Pose(InPose.GetPosition(), InPose.GetOrientation()),
			Scale(InScale.GetVector()),
			Color(InColor.GetColor()), Lifetime(InLifetime), bFrameLocked(bInFrameLocked)
		{
			MsgType = "visualization_msgs/Marker";
		}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}


		FString GetNamespace() const
		{
			return Ns;
		}

		int32 GetId() const
		{
			return Id;
		}

		EType GetMarkeType() const
		{
			return Type;
		}

		EAction GetActionTye() const
		{
			return Action;
		}

		geometry_msgs::Pose GetPose() const
		{
			return Pose;
		}

		geometry_msgs::Vector3 GetScale() const
		{
			return Scale;
		}

		std_msgs::ColorRGBA GetColor() const
		{
			return Color;
		}

		uint32 GetDuration() const
		{
			return Lifetime;
		}

		bool GetFrameLocked() const
		{
			return bFrameLocked;
		}

		TArray<geometry_msgs::Point> GetPoints() const
		{
			return Points;
		}
		TArray<std_msgs::ColorRGBA> GetColors() const
		{
			return Colors;
		}

		FString GetMeshResource() const
		{
			return MeshResource;
		}

		FString GetText() const
		{
			return Text;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetNamespace(FString InNs)
		{
			Ns = InNs;
		}

		void SetId(int32 InId)
		{
			Id = InId;
		}

		void SetMarkeType(EType InMarkerType)
		{
			Type = InMarkerType;
		}

		void SetActionTye(EAction InActionType)
		{
			Action = InActionType;
		}

		void SetPose(geometry_msgs::Pose InPose)
		{
			Pose = InPose;
		}

		void SetScale(geometry_msgs::Vector3 InScale)
		{
			Scale = InScale;
		}

		void SetColor(std_msgs::ColorRGBA InColor)
		{
			Color = InColor;
		}

		void SetDuration(uint32 InLifetime)
		{
			Lifetime = InLifetime;
		}

		void SetFrameLocked(bool bInFrameLocked)
		{
			bFrameLocked = bInFrameLocked;
		}

		void SetPoints(TArray<geometry_msgs::Point> InPoints)
		{
			Points = InPoints;
		}
		void SetColors(TArray<std_msgs::ColorRGBA> InColors)
		{
			Colors = InColors;
		}

		void SetMeshResource(FString InMeshREsource)
		{
			MeshResource = InMeshREsource;
		}

		void SetText(FString InText)
		{
			Text = InText;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
			Ns = JsonObject->GetStringField(TEXT("ns"));
			Id = JsonObject->GetIntegerField(TEXT("id"));
			Type = (EType)JsonObject->GetIntegerField(TEXT("type"));
			Action = (EAction)JsonObject->GetIntegerField(TEXT("action"));
			Pose = geometry_msgs::Pose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
			Scale = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("scale")));
			Color = std_msgs::ColorRGBA::GetFromJson(JsonObject->GetObjectField(TEXT("color")));

			TSharedPtr<FJsonObject> LifeTimeObj = JsonObject->GetObjectField("lifetime");
			Lifetime = LifeTimeObj->GetIntegerField("secs");
			bFrameLocked = JsonObject->GetBoolField(TEXT("frame_locked"));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArray = JsonObject->GetArrayField(TEXT("points"));
			for (auto & ptr : ValuesPtrArray)
			{
				geometry_msgs::Point point = geometry_msgs::Point::GetFromJson(ptr->AsObject());
				Points.Add(point);
			}

			ValuesPtrArray = JsonObject->GetArrayField(TEXT("colors"));
			for (auto & ptr : ValuesPtrArray)
			{
				std_msgs::ColorRGBA c = std_msgs::ColorRGBA::GetFromJson(ptr->AsObject());
				Colors.Add(c);
			}

			Text = JsonObject->GetStringField(TEXT("text"));
			MeshResource = JsonObject->GetStringField(TEXT("mesh_resource"));
			bMeshUseEmbeddedMaterials = JsonObject->GetBoolField(TEXT("mesh_use_embedded_materials"));
		}

		static Marker GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Marker Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			/*
			* TODO:IMPLEMENT
			* */
			return TEXT("Marker { header = ") + Header.ToString();
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetStringField(TEXT("ns"), Ns);
			Object->SetNumberField(TEXT("id"), Id);
			Object->SetNumberField(TEXT("type"), (uint8)Type);
			Object->SetNumberField(TEXT("action"), (uint8)Action);
			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
			Object->SetObjectField(TEXT("scale"), Scale.ToJsonObject());
			Object->SetObjectField(TEXT("color"), Color.ToJsonObject());

			TSharedPtr<FJsonObject> lifetime_ = MakeShareable<FJsonObject>(new FJsonObject());
			lifetime_->SetNumberField(TEXT("secs"), Lifetime);
			lifetime_->SetNumberField(TEXT("nsecs"), 0.0);
			Object->SetObjectField(TEXT("lifetime"), lifetime_);

			Object->SetBoolField(TEXT("frame_locked"), bFrameLocked);

			TArray<TSharedPtr<FJsonValue>> PointsPtrArray;
			for (auto & point : Points)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(point.ToJsonObject()));
				PointsPtrArray.Add(Ptr);
			}
			Object->SetArrayField(TEXT("points"), PointsPtrArray);

			TArray<TSharedPtr<FJsonValue>> ColorsPtrArray;
			for (auto & c : Colors)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(c.ToJsonObject()));
				ColorsPtrArray.Add(Ptr);
			}
			Object->SetArrayField(TEXT("colors"), ColorsPtrArray);

			Object->SetStringField(TEXT("text"), Text);
			Object->SetStringField(TEXT("mesh_resource"), MeshResource);
			Object->SetBoolField(TEXT("mesh_use_embedded_materials"), bMeshUseEmbeddedMaterials);

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