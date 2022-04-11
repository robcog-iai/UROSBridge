#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/Header.h"
#include "std_msgs/ColorRGBA.h"

namespace visualization_msgs
{
	class Marker : public FROSBridgeMsg
	{
	public:
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
			DEL= 2
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

	
		Marker()
		{
			MsgType = "visualization_msgs/Marker";
		}

		Marker(std_msgs::Header InHeader, FString InNs,
			EType InMarkerType, EAction InActionType,
			geometry_msgs::Pose InPose, geometry_msgs::Vector3 InScale,
			std_msgs::ColorRGBA InColor, uint32 InLifetime,
			bool bInFrameLocked,
			TArray<geometry_msgs::Point> InPoints, TArray<std_msgs::ColorRGBA> InColors,
			FString InText, FString InMeshResource, bool bInMeshUseEmbeddedMaterials) :
			Header(InHeader), Ns(InNs), Type(InMarkerType), Action(InActionType),  Pose(InPose.GetPosition(), InPose.GetOrientation()),
			Scale(InScale.GetVector()),
			Color(InColor.GetColor()), Lifetime(InLifetime), bFrameLocked(bInFrameLocked),
			Points(InPoints), Colors(InColors),
			Text(InText), MeshResource(InMeshResource), bMeshUseEmbeddedMaterials(bInMeshUseEmbeddedMaterials)
		{
			MsgType = "visualization_msgs/Marker";
		}

		static FString ETypeAsString(EType InType)
		{
			switch (InType)
			{
			case ARROW:
				return TEXT("ARROW");
				break;
			case CUBE:
				return TEXT("CUBE");
				break;
			case SPHERE:
				return TEXT("SPHERE");
				break;
			case CYLINDER:
				return TEXT("CYLINDER");
				break;
			case LINE_STRIP:
				return TEXT("LINE_STRIP");
				break;
			case LINE_LIST:
				return TEXT("LINE_LIST");
				break;
			case CUBE_LIST:
				return TEXT("CUBE_LIST");
				break;
			case SPHERE_LIST:
				return TEXT("SPHERE_LIST");
				break;
			case POINTS:
				return TEXT("POINTS");
				break;
			case TEXT_VIEW_FACING:
				return TEXT("TEXT_VIEW_FACING");
				break;
			case MESH_RESOURCE:
				return TEXT("MESH_RESOURCE");
				break;
			case TRIANGLE_LIST:
				return TEXT("TRIANGLE_LIST");
				break;
			default:
				return TEXT("Unknown");
			}
		}

		static FString EActionAsString(EAction InAction)
		{
			switch (InAction)
			{
			case ADD:
				return TEXT("ADD");
				break;
			case DEL:
				return TEXT("DEL");
				break;
			default:
				return TEXT("Unknown");
			}
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
			FString LifetimeString = TEXT("Duration {  secs = ") + FString::FromInt(Lifetime) +
				TEXT(" nsecs= ") + FString::FromInt(0.0) +
				TEXT(" } ");

			FString PointString = "[ ";
			for (auto &value : Points)
				PointString += value.ToString() + TEXT(", ");
			PointString += " ]";

			FString ColorString = "[ ";
			for (auto &value : Colors)
				ColorString += value.ToString() + TEXT(", ");
			ColorString += " ]";

			return TEXT("Marker { header = ") + Header.ToString() +
				TEXT(", ns = ") + Ns +
				TEXT(", id = ") + FString::FromInt(Id) +
				TEXT(", type = ") + ETypeAsString(Type) +
				TEXT(", action = ") + EActionAsString(Action) +
				TEXT(", pose = ") + Pose.ToString() +
				TEXT(", scale = ") + Scale.ToString() +
				TEXT(", color = ") + Color.ToString() +
				TEXT(", lifetime = ") + LifetimeString +
				TEXT(", frame_locked = ") + FString::FromInt(bFrameLocked) +
				TEXT(", points = ") + PointString +
				TEXT(", colors = ") + ColorString +
				TEXT(", text = ") + Text +
				TEXT(", mesh_resource") + MeshResource +
				TEXT(", mesh_use_embedded_materials") + FString::FromInt(bMeshUseEmbeddedMaterials) +
				TEXT(" } ");
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
