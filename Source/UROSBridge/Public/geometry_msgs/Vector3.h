#pragma once
#include "ROSBridgeMsg.h"

namespace geometry_msgs
{
	class Vector3 : public FROSBridgeMsg
	{
		double X;
		double Y;
		double Z;

	public:
		Vector3()
		{
			MsgType = "geometry_msgs/Vector3";
		}

		Vector3(
			double InX,
			double InY,
			double InZ) :
			X(InX),
			Y(InY),
			Z(InZ)
		{
			MsgType = "geometry_msgs/Vector3";
		}

		Vector3(const FVector& InVector)
		{
			MsgType = "geometry_msgs/Vector3";
			X = InVector.X;
			Y = InVector.Y;
			Z = InVector.Z;
		}

		~Vector3() override {}

		double GetX() const
		{
			return X;
		}

		double GetY() const
		{
			return Y;
		}

		double GetZ() const
		{
			return Z;
		}

		FVector GetVector() const
		{
			return FVector(X, Y, Z);
		}

		void SetX(double InX)
		{
			X = InX;
		}

		void SetY(double InY)
		{
			Y = InY;
		}

		void SetZ(double InZ)
		{
			Z = InZ;
		}

		void SetVector(const FVector& InVector)
		{
			X = InVector.X;
			Y = InVector.Y;
			Z = InVector.Z;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			X = (double)(JsonObject->GetNumberField(TEXT("x")));
			Y = (double)(JsonObject->GetNumberField(TEXT("y")));
			Z = (double)(JsonObject->GetNumberField(TEXT("z")));
		}

		static Vector3 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Vector3 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Vector3 { x = ") + FString::SanitizeFloat(X) +
				TEXT(", y = ") + FString::SanitizeFloat(Y) +
				TEXT(", z = ") + FString::SanitizeFloat(Z) + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetNumberField(TEXT("x"), X);
			Object->SetNumberField(TEXT("y"), Y);
			Object->SetNumberField(TEXT("z"), Z);
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
} // namespace geometry_msgs
