#pragma once
#include "ROSBridgeMsg.h"

namespace geometry_msgs
{
	class Point32 : public FROSBridgeMsg
	{
		float X;
		float Y;
		float Z;

	public:
		Point32()
		{
			MsgType = "geometry_msgs/Point32";
		}

		Point32(float InX, float InY, float InZ)
		{
			MsgType = "geometry_msgs/Point32";
			X = InX; Y = InY; Z = InZ;
		}

		Point32(FVector InVector)
		{
			MsgType = "geometry_msgs/Point32";
			X = InVector.X; Y = InVector.Y; Z = InVector.Z;
		}

		~Point32() override {}

		float GetX() const
		{
			return X;
		}

		float GetY() const
		{
			return Y;
		}

		float GetZ() const
		{
			return Z;
		}

		FVector GetVector() const
		{
			return FVector(X, Y, Z);
		}

		void SetX(float InX)
		{
			X = InX;
		}

		void SetY(float InY)
		{
			Y = InY;
		}

		void SetZ(float InZ)
		{
			Z = InZ;
		}

		void SetVector(const FVector& Vector)
		{
			X = Vector.X; Y = Vector.Y; Z = Vector.Z;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			X = (float)(JsonObject->GetNumberField(TEXT("x")));
			Y = (float)(JsonObject->GetNumberField(TEXT("y")));
			Z = (float)(JsonObject->GetNumberField(TEXT("z")));
		}

		static Point32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Point32 Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Point32 { x = ") + FString::SanitizeFloat(X) +
				TEXT(", y = ") + FString::SanitizeFloat(Y) +
				TEXT(", z = ") + FString::SanitizeFloat(Z) + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
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
} // geometry_msgs