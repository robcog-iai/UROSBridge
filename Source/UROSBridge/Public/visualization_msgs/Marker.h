#pragma once

#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/ColorRGBA.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/ColorRGBA.h"

namespace visualization_msgs
{
	class Marker : public FROSBridgeMsg
	{
		uint8 Arrow = 0;
		uint8 Cube = 1;
		uint8 Sphere = 2;
		uint8 Cylinder = 3;
		uint8 LineStrip = 4;
		uint8 LineList = 5;
		uint8 CubeList = 6;
		uint8 SphereList = 7;
		uint8 Points = 8;
		uint8 TextViewFacing = 9;
		uint8 MeshResource = 10;
		uint8 TriangleList = 11;
		uint8 Add = 0;
		uint8 Modify = 0;
		uint8 Delete = 2;
		uint8 Deleteall = 3;
		std_msgs::Header Header;
		FString Ns;
		int32 Id;
		int32 Type;
		int32 Action;
		geometry_msgs::Pose Pose;
		geometry_msgs::Vector3 Scale;
		std_msgs::ColorRGBA Color;
		uint32 Lifetime;
		bool FrameLocked;
		TArray<geometry_msgs::Point> Points2;
		TArray<std_msgs::ColorRGBA> Colors;
		FString Text;
		FString MeshResource2;
		bool MeshUseEmbeddedMaterials;
	public:
		Marker()
		{
			MsgType = "visualization_msgs/Marker";
		}

		Marker
		(
			uint8 InArrow,
			uint8 InCube,
			uint8 InSphere,
			uint8 InCylinder,
			uint8 InLineStrip,
			uint8 InLineList,
			uint8 InCubeList,
			uint8 InSphereList,
			uint8 InPoints,
			uint8 InTextViewFacing,
			uint8 InMeshResource,
			uint8 InTriangleList,
			uint8 InAdd,
			uint8 InModify,
			uint8 InDelete,
			uint8 InDeleteall,
			std_msgs::Header InHeader,
			FString InNs,
			int32 InId,
			int32 InType,
			int32 InAction,
			geometry_msgs::Pose InPose,
			geometry_msgs::Vector3 InScale,
			std_msgs::ColorRGBA InColor,
			uint32 InLifetime,
			bool InFrameLocked,
			const TArray<geometry_msgs::Point>& InPoints2,
			const TArray<std_msgs::ColorRGBA>& InColors,
			FString InText,
			FString InMeshResource2,
			bool InMeshUseEmbeddedMaterials
		):
			Arrow(InArrow = 0),
			Cube(InCube = 1),
			Sphere(InSphere = 2),
			Cylinder(InCylinder = 3),
			LineStrip(InLineStrip = 4),
			LineList(InLineList = 5),
			CubeList(InCubeList = 6),
			SphereList(InSphereList = 7),
			Points(InPoints = 8),
			TextViewFacing(InTextViewFacing = 9),
			MeshResource(InMeshResource = 10),
			TriangleList(InTriangleList = 11),
			Add(InAdd = 0),
			Modify(InModify = 0),
			Delete(InDelete = 2),
			Deleteall(InDeleteall = 3),
			Header(InHeader),
			Ns(InNs),
			Id(InId),
			Type(InType),
			Action(InAction),
			Pose(InPose),
			Scale(InScale),
			Color(InColor),
			Lifetime(InLifetime),
			FrameLocked(InFrameLocked),
			Points2(InPoints2),
			Colors(InColors),
			Text(InText),
			MeshResource2(InMeshResource2),
			MeshUseEmbeddedMaterials(InMeshUseEmbeddedMaterials)
		{
			MsgType = "visualization_msgs/Marker";
		}

		~Marker() override {}

		uint8 GetArrow() const
		{
			return Arrow;
		}

		uint8 GetCube() const
		{
			return Cube;
		}

		uint8 GetSphere() const
		{
			return Sphere;
		}

		uint8 GetCylinder() const
		{
			return Cylinder;
		}

		uint8 GetLineStrip() const
		{
			return LineStrip;
		}

		uint8 GetLineList() const
		{
			return LineList;
		}

		uint8 GetCubeList() const
		{
			return CubeList;
		}

		uint8 GetSphereList() const
		{
			return SphereList;
		}

		uint8 GetPoints() const
		{
			return Points;
		}

		uint8 GetTextViewFacing() const
		{
			return TextViewFacing;
		}

		uint8 GetMeshResource() const
		{
			return MeshResource;
		}

		uint8 GetTriangleList() const
		{
			return TriangleList;
		}

		uint8 GetAdd() const
		{
			return Add;
		}

		uint8 GetModify() const
		{
			return Modify;
		}

		uint8 GetDelete() const
		{
			return Delete;
		}

		uint8 GetDeleteall() const
		{
			return Deleteall;
		}

		std_msgs::Header GetHeader() const
		{
			return Header;
		}

		FString GetNs() const
		{
			return Ns;
		}

		int32 GetId() const
		{
			return Id;
		}

		int32 GetType() const
		{
			return Type;
		}

		int32 GetAction() const
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

		uint32 GetLifetime() const
		{
			return Lifetime;
		}

		bool GetFrameLocked() const
		{
			return FrameLocked;
		}

		TArray<geometry_msgs::Point> GetPoints2() const
		{
			return Points2;
		}

		TArray<std_msgs::ColorRGBA> GetColors() const
		{
			return Colors;
		}

		FString GetText() const
		{
			return Text;
		}

		FString GetMeshResource2() const
		{
			return MeshResource2;
		}

		bool GetMeshUseEmbeddedMaterials() const
		{
			return MeshUseEmbeddedMaterials;
		}

		void SetArrow(uint8 InArrow)
		{
			Arrow = InArrow;
		}

		void SetCube(uint8 InCube)
		{
			Cube = InCube;
		}

		void SetSphere(uint8 InSphere)
		{
			Sphere = InSphere;
		}

		void SetCylinder(uint8 InCylinder)
		{
			Cylinder = InCylinder;
		}

		void SetLineStrip(uint8 InLineStrip)
		{
			LineStrip = InLineStrip;
		}

		void SetLineList(uint8 InLineList)
		{
			LineList = InLineList;
		}

		void SetCubeList(uint8 InCubeList)
		{
			CubeList = InCubeList;
		}

		void SetSphereList(uint8 InSphereList)
		{
			SphereList = InSphereList;
		}

		void SetPoints(uint8 InPoints)
		{
			Points = InPoints;
		}

		void SetTextViewFacing(uint8 InTextViewFacing)
		{
			TextViewFacing = InTextViewFacing;
		}

		void SetMeshResource(uint8 InMeshResource)
		{
			MeshResource = InMeshResource;
		}

		void SetTriangleList(uint8 InTriangleList)
		{
			TriangleList = InTriangleList;
		}

		void SetAdd(uint8 InAdd)
		{
			Add = InAdd;
		}

		void SetModify(uint8 InModify)
		{
			Modify = InModify;
		}

		void SetDelete(uint8 InDelete)
		{
			Delete = InDelete;
		}

		void SetDeleteall(uint8 InDeleteall)
		{
			Deleteall = InDeleteall;
		}

		void SetHeader(std_msgs::Header InHeader)
		{
			Header = InHeader;
		}

		void SetNs(FString InNs)
		{
			Ns = InNs;
		}

		void SetId(int32 InId)
		{
			Id = InId;
		}

		void SetType(int32 InType)
		{
			Type = InType;
		}

		void SetAction(int32 InAction)
		{
			Action = InAction;
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

		void SetLifetime(uint32 InLifetime)
		{
			Lifetime = InLifetime;
		}

		void SetFrameLocked(bool InFrameLocked)
		{
			FrameLocked = InFrameLocked;
		}

		void SetPoints2(TArray<geometry_msgs::Point>& InPoints)
		{
			Points2 = InPoints;
		}

		void SetColors(TArray<std_msgs::ColorRGBA>& InColors)
		{
			Colors = InColors;
		}

		void SetText(FString InText)
		{
			Text = InText;
		}

		void SetMeshResource2(FString InMeshResource)
		{
			MeshResource2 = InMeshResource;
		}

		void SetMeshUseEmbeddedMaterials(bool InMeshUseEmbeddedMaterials)
		{
			MeshUseEmbeddedMaterials = InMeshUseEmbeddedMaterials;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Arrow = JsonObject->GetNumberField(TEXT("ARROW"));

			Cube = JsonObject->GetNumberField(TEXT("CUBE"));

			Sphere = JsonObject->GetNumberField(TEXT("SPHERE"));

			Cylinder = JsonObject->GetNumberField(TEXT("CYLINDER"));

			LineStrip = JsonObject->GetNumberField(TEXT("LINE_STRIP"));

			LineList = JsonObject->GetNumberField(TEXT("LINE_LIST"));

			CubeList = JsonObject->GetNumberField(TEXT("CUBE_LIST"));

			SphereList = JsonObject->GetNumberField(TEXT("SPHERE_LIST"));

			Points = JsonObject->GetNumberField(TEXT("POINTS"));

			TextViewFacing = JsonObject->GetNumberField(TEXT("TEXT_VIEW_FACING"));

			MeshResource = JsonObject->GetNumberField(TEXT("MESH_RESOURCE"));

			TriangleList = JsonObject->GetNumberField(TEXT("TRIANGLE_LIST"));

			Add = JsonObject->GetNumberField(TEXT("ADD"));

			Modify = JsonObject->GetNumberField(TEXT("MODIFY"));

			Delete = JsonObject->GetNumberField(TEXT("DELETE"));

			Deleteall = JsonObject->GetNumberField(TEXT("DELETEALL"));

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Ns = JsonObject->GetStringField(TEXT("ns"));

			Id = JsonObject->GetNumberField(TEXT("id"));

			Type = JsonObject->GetNumberField(TEXT("type"));

			Action = JsonObject->GetNumberField(TEXT("action"));

			Pose = geometry_msgs::Pose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));

			Scale = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("scale")));

			Color = std_msgs::ColorRGBA::GetFromJson(JsonObject->GetObjectField(TEXT("color")));

			Lifetime = JsonObject->GetNumberField(TEXT("lifetime"));

			FrameLocked = JsonObject->GetBoolField(TEXT("frame_locked"));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Points2.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : ValuesPtrArr)
				Points2.Add(geometry_msgs::Point::GetFromJson(ptr->AsObject()));

			Colors.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("colors"));
			for (auto &ptr : ValuesPtrArr)
				Colors.Add(std_msgs::ColorRGBA::GetFromJson(ptr->AsObject()));

			Text = JsonObject->GetStringField(TEXT("text"));

			MeshResource2 = JsonObject->GetStringField(TEXT("mesh_resource"));

			MeshUseEmbeddedMaterials = JsonObject->GetBoolField(TEXT("mesh_use_embedded_materials"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Arrow = BsonObject->GetNumberField(TEXT("ARROW"));

			Cube = BsonObject->GetNumberField(TEXT("CUBE"));

			Sphere = BsonObject->GetNumberField(TEXT("SPHERE"));

			Cylinder = BsonObject->GetNumberField(TEXT("CYLINDER"));

			LineStrip = BsonObject->GetNumberField(TEXT("LINE_STRIP"));

			LineList = BsonObject->GetNumberField(TEXT("LINE_LIST"));

			CubeList = BsonObject->GetNumberField(TEXT("CUBE_LIST"));

			SphereList = BsonObject->GetNumberField(TEXT("SPHERE_LIST"));

			Points = BsonObject->GetNumberField(TEXT("POINTS"));

			TextViewFacing = BsonObject->GetNumberField(TEXT("TEXT_VIEW_FACING"));

			MeshResource = BsonObject->GetNumberField(TEXT("MESH_RESOURCE"));

			TriangleList = BsonObject->GetNumberField(TEXT("TRIANGLE_LIST"));

			Add = BsonObject->GetNumberField(TEXT("ADD"));

			Modify = BsonObject->GetNumberField(TEXT("MODIFY"));

			Delete = BsonObject->GetNumberField(TEXT("DELETE"));

			Deleteall = BsonObject->GetNumberField(TEXT("DELETEALL"));

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Ns = BsonObject->GetStringField(TEXT("ns"));

			Id = BsonObject->GetNumberField(TEXT("id"));

			Type = BsonObject->GetNumberField(TEXT("type"));

			Action = BsonObject->GetNumberField(TEXT("action"));

			Pose = geometry_msgs::Pose::GetFromBson(BsonObject->GetObjectField(TEXT("pose")));

			Scale = geometry_msgs::Vector3::GetFromBson(BsonObject->GetObjectField(TEXT("scale")));

			Color = std_msgs::ColorRGBA::GetFromBson(BsonObject->GetObjectField(TEXT("color")));

			Lifetime = BsonObject->GetNumberField(TEXT("lifetime"));

			FrameLocked = BsonObject->GetBoolField(TEXT("frame_locked"));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Points2.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : ValuesPtrArr)
				Points2.Add(geometry_msgs::Point::GetFromBson(ptr->AsObject()));

			Colors.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("colors"));
			for (auto &ptr : ValuesPtrArr)
				Colors.Add(std_msgs::ColorRGBA::GetFromBson(ptr->AsObject()));

			Text = BsonObject->GetStringField(TEXT("text"));

			MeshResource2 = BsonObject->GetStringField(TEXT("mesh_resource"));

			MeshUseEmbeddedMaterials = BsonObject->GetBoolField(TEXT("mesh_use_embedded_materials"));

		}

		static Marker GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Marker Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Marker GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Marker Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("ARROW"), Arrow);
			Object->SetNumberField(TEXT("CUBE"), Cube);
			Object->SetNumberField(TEXT("SPHERE"), Sphere);
			Object->SetNumberField(TEXT("CYLINDER"), Cylinder);
			Object->SetNumberField(TEXT("LINE_STRIP"), LineStrip);
			Object->SetNumberField(TEXT("LINE_LIST"), LineList);
			Object->SetNumberField(TEXT("CUBE_LIST"), CubeList);
			Object->SetNumberField(TEXT("SPHERE_LIST"), SphereList);
			Object->SetNumberField(TEXT("POINTS"), Points);
			Object->SetNumberField(TEXT("TEXT_VIEW_FACING"), TextViewFacing);
			Object->SetNumberField(TEXT("MESH_RESOURCE"), MeshResource);
			Object->SetNumberField(TEXT("TRIANGLE_LIST"), TriangleList);
			Object->SetNumberField(TEXT("ADD"), Add);
			Object->SetNumberField(TEXT("MODIFY"), Modify);
			Object->SetNumberField(TEXT("DELETE"), Delete);
			Object->SetNumberField(TEXT("DELETEALL"), Deleteall);
			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());
			Object->SetStringField(TEXT("ns"), Ns);
			Object->SetNumberField(TEXT("id"), Id);
			Object->SetNumberField(TEXT("type"), Type);
			Object->SetNumberField(TEXT("action"), Action);
			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
			Object->SetObjectField(TEXT("scale"), Scale.ToJsonObject());
			Object->SetObjectField(TEXT("color"), Color.ToJsonObject());
			Object->SetNumberField(TEXT("lifetime"), Lifetime);
			Object->SetBoolField(TEXT("frame_locked"), FrameLocked);
			TArray<TSharedPtr<FJsonValue>> PointsArray;
			for (auto &val : Points2)
				PointsArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("points"), PointsArray);
			TArray<TSharedPtr<FJsonValue>> ColorsArray;
			for (auto &val : Colors)
				ColorsArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("colors"), ColorsArray);
			Object->SetStringField(TEXT("text"), Text);
			Object->SetStringField(TEXT("mesh_resource"), MeshResource2);
			Object->SetBoolField(TEXT("mesh_use_embedded_materials"), MeshUseEmbeddedMaterials);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetNumberField(TEXT("ARROW"), Arrow);
			Object->SetNumberField(TEXT("CUBE"), Cube);
			Object->SetNumberField(TEXT("SPHERE"), Sphere);
			Object->SetNumberField(TEXT("CYLINDER"), Cylinder);
			Object->SetNumberField(TEXT("LINE_STRIP"), LineStrip);
			Object->SetNumberField(TEXT("LINE_LIST"), LineList);
			Object->SetNumberField(TEXT("CUBE_LIST"), CubeList);
			Object->SetNumberField(TEXT("SPHERE_LIST"), SphereList);
			Object->SetNumberField(TEXT("POINTS"), Points);
			Object->SetNumberField(TEXT("TEXT_VIEW_FACING"), TextViewFacing);
			Object->SetNumberField(TEXT("MESH_RESOURCE"), MeshResource);
			Object->SetNumberField(TEXT("TRIANGLE_LIST"), TriangleList);
			Object->SetNumberField(TEXT("ADD"), Add);
			Object->SetNumberField(TEXT("MODIFY"), Modify);
			Object->SetNumberField(TEXT("DELETE"), Delete);
			Object->SetNumberField(TEXT("DELETEALL"), Deleteall);
			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());
			Object->SetStringField(TEXT("ns"), Ns);
			Object->SetNumberField(TEXT("id"), Id);
			Object->SetNumberField(TEXT("type"), Type);
			Object->SetNumberField(TEXT("action"), Action);
			Object->SetObjectField(TEXT("pose"), Pose.ToBsonObject());
			Object->SetObjectField(TEXT("scale"), Scale.ToBsonObject());
			Object->SetObjectField(TEXT("color"), Color.ToBsonObject());
			Object->SetNumberField(TEXT("lifetime"), Lifetime);
			Object->SetBoolField(TEXT("frame_locked"), FrameLocked);
			TArray<TSharedPtr<FBsonValue>> PointsArray;
			for (auto &val : Points2)
				PointsArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("points"), PointsArray);
			TArray<TSharedPtr<FBsonValue>> ColorsArray;
			for (auto &val : Colors)
				ColorsArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("colors"), ColorsArray);
			Object->SetStringField(TEXT("text"), Text);
			Object->SetStringField(TEXT("mesh_resource"), MeshResource2);
			Object->SetBoolField(TEXT("mesh_use_embedded_materials"), MeshUseEmbeddedMaterials);
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