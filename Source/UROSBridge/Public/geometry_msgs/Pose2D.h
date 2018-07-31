#pragma once

#include "ROSBridgeMsg.h"


namespace geometry_msgs
{
	class Pose2D : public FROSBridgeMsg
	{
		double X;
		double Y;
		double Theta;
	public:
		Pose2D()
		{
			MsgType = "geometry_msgs/Pose2D";
		}

		Pose2D
		(
			double InX,
			double InY,
			double InTheta
		):
			X(InX),
			Y(InY),
			Theta(InTheta)
		{
			MsgType = "geometry_msgs/Pose2D";
		}

		~Pose2D() override {}

		double GetX() const
		{
			return X;
		}

		double GetY() const
		{
			return Y;
		}

		double GetTheta() const
		{
			return Theta;
		}

		void SetX(double InX)
		{
			X = InX;
		}

		void SetY(double InY)
		{
			Y = InY;
		}

		void SetTheta(double InTheta)
		{
			Theta = InTheta;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			X = JsonObject->GetNumberField(TEXT("x"));

			Y = JsonObject->GetNumberField(TEXT("y"));

			Theta = JsonObject->GetNumberField(TEXT("theta"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			X = BsonObject->GetNumberField(TEXT("x"));

			Y = BsonObject->GetNumberField(TEXT("y"));

			Theta = BsonObject->GetNumberField(TEXT("theta"));

		}

		static Pose2D GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Pose2D Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Pose2D GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Pose2D Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("x"), X);
			Object->SetNumberField(TEXT("y"), Y);
			Object->SetNumberField(TEXT("theta"), Theta);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetNumberField(TEXT("x"), X);
			Object->SetNumberField(TEXT("y"), Y);
			Object->SetNumberField(TEXT("theta"), Theta);
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