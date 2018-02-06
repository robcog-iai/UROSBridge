#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"

namespace geometry_msgs
{
	class Inertia : public FROSBridgeMsg
	{
		double M;
		geometry_msgs::Vector3 Com;
		double Ixx, Ixy, Ixz, Iyy, Iyz, Izz;

	public:
		Inertia()
		{
			MsgType = "geometry_msgs/Inertia";
		}

		Inertia
		(double InM, geometry_msgs::Vector3 InCom,
			double InIxx, double InIxy, double InIxz, double InIyy, double InIyz, double InIzz) :
			M(InM), Com(InCom), Ixx(InIxx), Ixy(InIxy), Ixz(InIxz), Iyy(InIyy), Iyz(InIyz), Izz(InIzz)
		{
			MsgType = "geometry_msgs/Inertia";
		}

		~Inertia() override {}

		geometry_msgs::Vector3 GetCom() const
		{
			return Com;
		}

		double GetM() const 
		{
			return M;
		}

		double GetIxx() const 
		{
			return Ixx;
		}

		double GetIxy() const 
		{
			return Ixy;
		}

		double GetIxz() const 
		{
			return Ixz; 
		}

		double GetIyy() const 
		{
			return Iyy;
		}

		double GetIyz() const 
		{
			return Iyz;
		}

		double GetIzz() const 
		{
			return Izz;
		}

		void SetCom(geometry_msgs::Vector3 InCom)
		{
			Com = InCom;
		}

		void SetM(double InM) 
		{ 
			M = InM;
		}

		void SetIxx(double InIxx) 
		{
			Ixx = InIxx;
		}

		void SetIxy(double InIxy) 
		{
			Ixy = InIxy;
		}

		void SetIxz(double InIxz) 
		{
			Ixz = InIxz;
		}

		void SetIyy(double InIyy) 
		{
			Iyy = InIyy;
		}

		void SetIyz(double InIyz) 
		{
			Iyz = InIyz;
		}

		void SetIzz(double InIzz)
		{
			Izz = InIzz;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			M = JsonObject->GetNumberField(TEXT("m"));
			Com = geometry_msgs::Vector3::GetFromJson(JsonObject->GetObjectField(TEXT("com")));
			Ixx = JsonObject->GetNumberField(TEXT("ixx"));
			Ixy = JsonObject->GetNumberField(TEXT("ixy"));
			Ixz = JsonObject->GetNumberField(TEXT("ixz"));
			Iyy = JsonObject->GetNumberField(TEXT("iyy"));
			Iyz = JsonObject->GetNumberField(TEXT("iyz"));
			Izz = JsonObject->GetNumberField(TEXT("izz"));
		}

		static Inertia GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Inertia Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Inertia { m = ") + FString::SanitizeFloat(M) +
				TEXT(", com = ") + Com.ToString() +
				TEXT(", ixx = ") + FString::SanitizeFloat(Ixx) +
				TEXT(", ixy = ") + FString::SanitizeFloat(Ixy) +
				TEXT(", ixz = ") + FString::SanitizeFloat(Ixz) +
				TEXT(", iyy = ") + FString::SanitizeFloat(Iyy) +
				TEXT(", iyz = ") + FString::SanitizeFloat(Iyz) +
				TEXT(", izz = ") + FString::SanitizeFloat(Izz) + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetNumberField(TEXT("m"), M);
			Object->SetObjectField(TEXT("com"), Com.ToJsonObject());
			Object->SetNumberField(TEXT("ixx"), Ixx);
			Object->SetNumberField(TEXT("ixy"), Ixy);
			Object->SetNumberField(TEXT("ixz"), Ixz);
			Object->SetNumberField(TEXT("iyy"), Iyy);
			Object->SetNumberField(TEXT("iyz"), Iyz);
			Object->SetNumberField(TEXT("izz"), Izz);
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
} // geometry_msgs