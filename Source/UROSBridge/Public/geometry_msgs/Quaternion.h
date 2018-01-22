#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsQuaternion : public FROSBridgeMsg
{
    double x; 
    double y;
    double z;
    double w; 

public:
    FROSBridgeMsgGeometrymsgsQuaternion()
    {
        Type = "geometry_msgs/Quaternion";
    }

    FROSBridgeMsgGeometrymsgsQuaternion(double x_, double y_, double z_, double w_)
    {
        Type = "geometry_msgs/Quaternion";
        x = x_; y = y_; z = z_;  w = w_; 
    }

    FROSBridgeMsgGeometrymsgsQuaternion(const FQuat& Quat)
    {
        Type = "geometry_msgs/Quaternion";
        x = Quat.X; y = Quat.Y; z = Quat.Z; w = Quat.W;
    }

    ~FROSBridgeMsgGeometrymsgsQuaternion() override {}

    double GetX() const 
    {
        return x;
    }

    double GetY() const
    {
        return y;
    }

    double GetZ() const
    {
        return z;
    }

    double GetW() const
    {
        return w;
    }

    FQuat GetQuat() const 
    {
        return FQuat(x, y, z, w); 
    }

    void SetX(double x_)
    {
        x = x_; 
    }

    void SetY(double y_)
    {
        y = y_;
    }

    void SetZ(double z_)
    {
        z = z_;
    }

    void SetW(double w_)
    {
        w = w_;
    }

    void SetQuat(const FQuat& Quat)
    {
        x = Quat.X; y = Quat.Y; z = Quat.Z; w = Quat.W;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        x = (double)(JsonObject->GetNumberField(TEXT("x"))); 
        y = (double)(JsonObject->GetNumberField(TEXT("y")));
        z = (double)(JsonObject->GetNumberField(TEXT("z")));
        w = (double)(JsonObject->GetNumberField(TEXT("w")));
    }

    static FROSBridgeMsgGeometrymsgsQuaternion GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsQuaternion Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Quaternion { x = ") + FString::SanitizeFloat(x) + 
                     TEXT(", y = ") + FString::SanitizeFloat(y) +
                     TEXT(", z = ") + FString::SanitizeFloat(z) + 
                     TEXT(", w = ") + FString::SanitizeFloat(w) +TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("x"), x);
        Object->SetNumberField(TEXT("y"), y);
        Object->SetNumberField(TEXT("z"), z);
        Object->SetNumberField(TEXT("w"), w);
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
	class Quaternion : public FROSBridgeMsg
	{
		double X;
		double Y;
		double Z;
		double W;

	public:
		Quaternion()
		{
			Type = "geometry_msgs/Quaternion";
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
			Type = "geometry_msgs/Quaternion";
		}

		Quaternion(const FQuat& Quat)
		{
			Type = "geometry_msgs/Quaternion";
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