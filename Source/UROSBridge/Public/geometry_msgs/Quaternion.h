#pragma once
#include "ROSBridgeMsg.h"

namespace geometry_msgs
{
	class Quaternion : public FROSBridgeMsg
	{
		double X;
		double Y;
		double Z;
		double W;

	public:
		Quaternion()
		{
			MsgType = "geometry_msgs/Quaternion";
		}

		Quaternion(
			double InX,
			double InY,
			double InZ,
			double InW) :
			X(InX),
			Y(InY),
			Z(InZ),
			W(InW)
		{
			MsgType = "geometry_msgs/Quaternion";
		}

		Quaternion(const FQuat& Quat)
		{
			MsgType = "geometry_msgs/Quaternion";
			X = Quat.X;
			Y = Quat.Y;
			Z = Quat.Z;
			W = Quat.W;
		}

		~Quaternion() override {}

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

		double GetW() const
		{
			return W;
		}

		FQuat GetQuat() const
		{
			return FQuat(X, Y, Z, W);
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

		void SetW(double InW)
		{
			W = InW;
		}

		void SetQuat(const FQuat& InQuat)
		{
			X = InQuat.X;
			Y = InQuat.Y;
			Z = InQuat.Z;
			W = InQuat.W;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			X = (double)(JsonObject->GetNumberField(TEXT("x")));
			Y = (double)(JsonObject->GetNumberField(TEXT("y")));
			Z = (double)(JsonObject->GetNumberField(TEXT("z")));
			W = (double)(JsonObject->GetNumberField(TEXT("w")));
		}

		static Quaternion GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Quaternion Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Quaternion { x = ") + FString::SanitizeFloat(X) +
				TEXT(", y = ") + FString::SanitizeFloat(Y) +
				TEXT(", z = ") + FString::SanitizeFloat(Z) +
				TEXT(", w = ") + FString::SanitizeFloat(W) + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetNumberField(TEXT("x"), X);
			Object->SetNumberField(TEXT("y"), Y);
			Object->SetNumberField(TEXT("z"), Z);
			Object->SetNumberField(TEXT("w"), W);
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