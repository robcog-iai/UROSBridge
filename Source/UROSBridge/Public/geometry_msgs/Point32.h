#pragma once
#include "ROSBridgeMsg.h"

class FROSBridgeMsgGeometrymsgsPoint32 : public FROSBridgeMsg
{
    float x; 
    float y;
    float z;

public:
    FROSBridgeMsgGeometrymsgsPoint32()
    {
        Type = "geometry_msgs/Point32";
    }

    FROSBridgeMsgGeometrymsgsPoint32(float x_, float y_, float z_)
    {
        Type = "geometry_msgs/Point32";
        x = x_; y = y_; z = z_; 
    }

    FROSBridgeMsgGeometrymsgsPoint32(FVector Vector)
    {
        Type = "geometry_msgs/Point32";
        x = Vector.X; y = Vector.Y; z = Vector.Z; 
    }

    ~FROSBridgeMsgGeometrymsgsPoint32() override {}

    float GetX() const 
    {
        return x;
    }

    float GetY() const
    {
        return y;
    }

    float GetZ() const
    {
        return z;
    }

    FVector GetVector() const 
    {
        return FVector(x, y, z); 
    }

    void SetX(float x_)
    {
        x = x_; 
    }

    void SetY(float y_)
    {
        y = y_;
    }

    void SetZ(float z_)
    {
        z = z_;
    }

    void SetVector(const FVector & Vector)
    {
        x = Vector.X; y = Vector.Y; z = Vector.Z;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        x = (float)(JsonObject->GetNumberField(TEXT("x"))); 
        y = (float)(JsonObject->GetNumberField(TEXT("y")));
        z = (float)(JsonObject->GetNumberField(TEXT("z")));
    }

    static FROSBridgeMsgGeometrymsgsPoint32 GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPoint32 Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Point32 { x = ") + FString::SanitizeFloat(x) + 
                       TEXT(", y = ") + FString::SanitizeFloat(y) +
                       TEXT(", z = ") + FString::SanitizeFloat(z) + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("x"), x);
        Object->SetNumberField(TEXT("y"), y);
        Object->SetNumberField(TEXT("z"), z);
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
	class Point32 : public FROSBridgeMsg
	{
		float X;
		float Y;
		float Z;

	public:
		Point32()
		{
			Type = "geometry_msgs/Point32";
		}

		Point32(float InX, float InY, float InZ)
		{
			Type = "geometry_msgs/Point32";
			X = InX; Y = InY; Z = InZ;
		}

		Point32(FVector InVector)
		{
			Type = "geometry_msgs/Point32";
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