#pragma once

#include "ROSBridgeMsg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/ColorRGBA.h"
#include "geometry_msgs/Point.h"


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
			DEL = 2
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
		bool FrameLocked;
		TArray<geometry_msgs::Point> Points;
		TArray<std_msgs::ColorRGBA> Colors;
		FString Text;
		FString MeshResource;
		bool MeshUseEmbeddedMaterials;
	
		Marker()
		{
			MsgType = TEXT("visualization_msgs/Marker");
		}
		
		Marker(std_msgs::Header InHeader,
			FString InNs,
			int32 InId,
			EType InType,
			EAction InAction,
			geometry_msgs::Pose InPose,
			geometry_msgs::Vector3 InScale,
			std_msgs::ColorRGBA InColor,
			uint32 InLifetime,
			bool InFrameLocked,
			TArray<geometry_msgs::Point> InPoints,
			TArray<std_msgs::ColorRGBA> InColors,
			FString InText,
			FString InMeshResource,
			bool InMeshUseEmbeddedMaterials)
			:
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
			Points(InPoints),
			Colors(InColors),
			Text(InText),
			MeshResource(InMeshResource),
			MeshUseEmbeddedMaterials(InMeshUseEmbeddedMaterials)
		{
			MsgType = TEXT("visualization_msgs/Marker");
		}

		~Marker() override {}

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

		// Getters 
		std_msgs::Header GetHeader() const { return Header; }
		FString GetNs() const { return Ns; }
		FString GetNamespace() const { return Ns; }
		int32 GetId() const { return Id; }
		EType GetType() const { return Type; }
		EType GetMarkeType() const { return Type; }
		EAction GetAction() const { return Action; }
		EAction GetActionTye() const { return Action; }
		geometry_msgs::Pose GetPose() const { return Pose; }
		geometry_msgs::Vector3 GetScale() const { return Scale; }
		std_msgs::ColorRGBA GetColor() const { return Color; }
		uint32 GetLifetime() const { return Lifetime; }
		uint32 GetDuration() const { return Lifetime; }
		bool GetFrameLocked() const { return FrameLocked; }
		TArray<geometry_msgs::Point> GetPoints() const { return Points; }
		TArray<std_msgs::ColorRGBA> GetColors() const { return Colors; }
		FString GetText() const { return Text; }
		FString GetMeshResource() const { return MeshResource; }
		bool GetMeshUseEmbeddedMaterials() const { return MeshUseEmbeddedMaterials; }

		// Setters 
		void SetHeader(std_msgs::Header InHeader) { Header = InHeader; }
		void SetNs(FString InNs) { Ns = InNs; }
		void SetNamespace(FString InNs) { Ns = InNs; }
		void SetId(int32 InId) { Id = InId; }
		void SetType(EType InType) { Type = InType; }
		void SetMarkeType(EType InType) { Type = InType; }
		void SetAction(EAction InAction) { Action = InAction; }
		void SetActionTye(EAction InAction) { Action = InAction; }
		void SetPose(geometry_msgs::Pose InPose) { Pose = InPose; }
		void SetScale(geometry_msgs::Vector3 InScale) { Scale = InScale; }
		void SetColor(std_msgs::ColorRGBA InColor) { Color = InColor; }
		void SetLifetime(uint32 InLifetime) { Lifetime = InLifetime; }
		void SetDuration(uint32 InLifetime) { Lifetime = InLifetime; }
		void SetFrameLocked(bool InFrameLocked) { FrameLocked = InFrameLocked; }
		void SetPoints(TArray<geometry_msgs::Point> InPoints) { Points = InPoints; }
		void SetColors(TArray<std_msgs::ColorRGBA> InColors) { Colors = InColors; }
		void SetText(FString InText) { Text = InText; }
		void SetMeshResource(FString InMeshResource) { MeshResource = InMeshResource; }
		void SetMeshUseEmbeddedMaterials(bool InMeshUseEmbeddedMaterials) { MeshUseEmbeddedMaterials = InMeshUseEmbeddedMaterials; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromJson(JsonObject->GetObjectField(TEXT("header")));

			Ns = JsonObject->GetStringField(TEXT("ns"));

			Id = JsonObject->GetNumberField(TEXT("id"));

			Type = (EType)JsonObject->GetNumberField(TEXT("type"));

			Action = (EAction)JsonObject->GetNumberField(TEXT("action"));

			Pose = geometry_msgs::Pose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));

			Scale = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("scale")));

			Color = std_msgs::ColorRGBA::GetFromJson(JsonObject->GetObjectField(TEXT("color")));

			Lifetime = JsonObject->GetNumberField(TEXT("lifetime"));

			FrameLocked = JsonObject->GetBoolField(TEXT("frame_locked"));

			Points.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : ValuesPtrArr)
				Points.Add(geometry_msgs::Point::GetFromJson(ptr->AsObject()));

			Colors.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("colors"));
			for (auto &ptr : ValuesPtrArr)
				Colors.Add(std_msgs::ColorRGBA::GetFromJson(ptr->AsObject()));

			Text = JsonObject->GetStringField(TEXT("text"));

			MeshResource = JsonObject->GetStringField(TEXT("mesh_resource"));

			MeshUseEmbeddedMaterials = JsonObject->GetBoolField(TEXT("mesh_use_embedded_materials"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Header = std_msgs::Header::GetFromBson(BsonObject->GetObjectField(TEXT("header")));

			Ns = BsonObject->GetStringField(TEXT("ns"));

			Id = BsonObject->GetNumberField(TEXT("id"));

			Type = (EType)BsonObject->GetNumberField(TEXT("type"));

			Action = (EAction)BsonObject->GetNumberField(TEXT("action"));

			Pose = geometry_msgs::Pose::GetFromBson(BsonObject->GetObjectField(TEXT("pose")));

			Scale = geometry_msgs::Vector3::GetFromBson(BsonObject->GetObjectField(TEXT("scale")));

			Color = std_msgs::ColorRGBA::GetFromBson(BsonObject->GetObjectField(TEXT("color")));

			Lifetime = BsonObject->GetNumberField(TEXT("lifetime"));

			FrameLocked = BsonObject->GetBoolField(TEXT("frame_locked"));

			Points.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("points"));
			for (auto &ptr : ValuesPtrArr)
				Points.Add(geometry_msgs::Point::GetFromBson(ptr->AsObject()));

			Colors.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("colors"));
			for (auto &ptr : ValuesPtrArr)
				Colors.Add(std_msgs::ColorRGBA::GetFromBson(ptr->AsObject()));

			Text = BsonObject->GetStringField(TEXT("text"));

			MeshResource = BsonObject->GetStringField(TEXT("mesh_resource"));

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

			Object->SetObjectField(TEXT("header"), Header.ToJsonObject());

			Object->SetStringField(TEXT("ns"), Ns);

			Object->SetNumberField(TEXT("id"), Id);

			Object->SetNumberField(TEXT("type"), Type);

			Object->SetNumberField(TEXT("action"), Action);

			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());

			Object->SetObjectField(TEXT("scale"), Scale.ToJsonObject());

			Object->SetObjectField(TEXT("color"), Color.ToJsonObject());

			TSharedPtr<FJsonObject> lifetime_ = MakeShareable<FJsonObject>(new FJsonObject());
			lifetime_->SetNumberField(TEXT("secs"), Lifetime);
			lifetime_->SetNumberField(TEXT("nsecs"), 0.0);
			Object->SetObjectField(TEXT("lifetime"), lifetime_);

			Object->SetBoolField(TEXT("frame_locked"), FrameLocked);

			TArray<TSharedPtr<FJsonValue>> PointsArray;
			for (auto &val : Points)
				PointsArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("points"), PointsArray);

			TArray<TSharedPtr<FJsonValue>> ColorsArray;
			for (auto &val : Colors)
				ColorsArray.Add(MakeShareable(new FJsonValueObject(val.ToJsonObject())));
			Object->SetArrayField(TEXT("colors"), ColorsArray);

			Object->SetStringField(TEXT("text"), Text);

			Object->SetStringField(TEXT("mesh_resource"), MeshResource);

			Object->SetBoolField(TEXT("mesh_use_embedded_materials"), MeshUseEmbeddedMaterials);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("header"), Header.ToBsonObject());

			Object->SetStringField(TEXT("ns"), Ns);

			Object->SetNumberField(TEXT("id"), Id);

			Object->SetNumberField(TEXT("type"), Type);

			Object->SetNumberField(TEXT("action"), Action);

			Object->SetObjectField(TEXT("pose"), Pose.ToBsonObject());

			Object->SetObjectField(TEXT("scale"), Scale.ToBsonObject());

			Object->SetObjectField(TEXT("color"), Color.ToBsonObject());

			TSharedPtr<FBsonObject> lifetime_ = MakeShareable<FBsonObject>(new FBsonObject());
			lifetime_->SetNumberField(TEXT("secs"), Lifetime);
			lifetime_->SetNumberField(TEXT("nsecs"), 0.0);
			Object->SetObjectField(TEXT("lifetime"), lifetime_);

			Object->SetBoolField(TEXT("frame_locked"), FrameLocked);

			TArray<TSharedPtr<FBsonValue>> PointsArray;
			for (auto &val : Points)
				PointsArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("points"), PointsArray);

			TArray<TSharedPtr<FBsonValue>> ColorsArray;
			for (auto &val : Colors)
				ColorsArray.Add(MakeShareable(new FBsonValueObject(val.ToBsonObject())));
			Object->SetArrayField(TEXT("colors"), ColorsArray);

			Object->SetStringField(TEXT("text"), Text);

			Object->SetStringField(TEXT("mesh_resource"), MeshResource);

			Object->SetBoolField(TEXT("mesh_use_embedded_materials"), MeshUseEmbeddedMaterials);

			return Object;

		}

		virtual FString ToString() const override
		{
			FString LifetimeString = TEXT("Duration {  secs = ") + FString::FromInt(Lifetime) +
				TEXT(" nsecs= ") + FString::FromInt(0.0) +
				TEXT(" } ");

			FString PointsString = "[ ";
			for (auto &value : Points)
				PointsString += value.ToString() + TEXT(", ");
			PointsString += " ] ";
			FString ColorsString = "[ ";
			for (auto &value : Colors)
				ColorsString += value.ToString() + TEXT(", ");
			ColorsString += " ] ";
			return TEXT("Marker {  header = ") + Header.ToString() +
				TEXT(", ns = ") + Ns +
				TEXT(", id = ") + FString::FromInt(Id) +
				TEXT(", type = ") + ETypeAsString(Type) +
				TEXT(", action = ") + EActionAsString(Action) +
				TEXT(", pose = ") + Pose.ToString() +
				TEXT(", scale = ") + Scale.ToString() +
				TEXT(", color = ") + Color.ToString() +
				TEXT(", lifetime = ") + LifetimeString +
				TEXT(", frame_locked = ") + FString::FromInt(FrameLocked) +
				TEXT(", points =") + PointsString +
				TEXT(", colors =") + ColorsString +
				TEXT(", text = ") + Text +
				TEXT(", mesh_resource = ") + MeshResource +
				TEXT(", mesh_use_embedded_materials = ") + FString::FromInt(MeshUseEmbeddedMaterials) +
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