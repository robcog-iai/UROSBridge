#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsPose2D : public FROSBridgeMsg
{
    double x; 
    double y;
    double theta;

public:
    FROSBridgeMsgGeometrymsgsPose2D()
    {
        MsgType = "geometry_msgs/Pose2D";
    }

    FROSBridgeMsgGeometrymsgsPose2D(double x_, double y_, double theta_)
    {
        MsgType = "geometry_msgs/Pose2D";
        x = x_; y = y_; theta = theta_; 
    }

    FROSBridgeMsgGeometrymsgsPose2D(FVector Vector)
    {
        MsgType = "geometry_msgs/Pose2D";
        x = Vector.X; y = Vector.Y; theta = Vector.Z; 
    }

    ~FROSBridgeMsgGeometrymsgsPose2D() override {}

    double GetX() const 
    {
        return x;
    }

    double GetY() const
    {
        return y;
    }

    double GetTheta() const
    {
        return theta;
    }

    FVector GetVector() const 
    {
        return FVector(x, y, theta); 
    }

    void SetX(double x_)
    {
        x = x_; 
    }

    void SetY(double y_)
    {
        y = y_;
    }

    void SetTheta(double theta_)
    {
        theta = theta_;
    }

    void SetVector(const FVector & Vector)
    {
        x = Vector.X; y = Vector.Y; theta = Vector.Z;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        x = (double)(JsonObject->GetNumberField(TEXT("x"))); 
        y = (double)(JsonObject->GetNumberField(TEXT("y")));
        theta = (double)(JsonObject->GetNumberField(TEXT("theta")));
    }

    static FROSBridgeMsgGeometrymsgsPose2D GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPose2D Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Pose2D { x = ") + FString::SanitizeFloat(x) + 
                     TEXT(", y = ") + FString::SanitizeFloat(y) +
                     TEXT(", theta = ") + FString::SanitizeFloat(theta) + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("x"), x);
        Object->SetNumberField(TEXT("y"), y);
        Object->SetNumberField(TEXT("theta"), theta);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};

/************************************************************************/
/* Namespace version                                                    */
/************************************************************************/
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

		Pose2D(double InX, double InY, double InTheta)
		{
			MsgType = "geometry_msgs/Pose2D";
			X = InX; Y = InY; Theta = InTheta;
		}

		Pose2D(FVector InVector)
		{
			MsgType = "geometry_msgs/Pose2D";
			X = InVector.X; Y = InVector.Y; Theta = InVector.Z;
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

		FVector GetVector() const
		{
			return FVector(X, Y, Theta);
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

		void SetVector(const FVector& InVector)
		{
			X = InVector.X; Y = InVector.Y; Theta = InVector.Z;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			X = (double)(JsonObject->GetNumberField(TEXT("x")));
			Y = (double)(JsonObject->GetNumberField(TEXT("y")));
			Theta = (double)(JsonObject->GetNumberField(TEXT("theta")));
		}

		static Pose2D GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Pose2D Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			return TEXT("Pose2D { x = ") + FString::SanitizeFloat(X) +
				TEXT(", y = ") + FString::SanitizeFloat(Y) +
				TEXT(", theta = ") + FString::SanitizeFloat(Theta) + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
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
} // namespace geometry_msgs