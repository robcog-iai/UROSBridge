#pragma once

#include "ROSBridgeMsg.h"


namespace geometry_msgs
{
	class Point : public FROSBridgeMsg
	{
		double X;
		double Y;
		double Z;
	public:
		Point()
		{
			MsgType = TEXT("geometry_msgs/Point");
		}
		
		Point(double InX,
			double InY,
			double InZ)
			:
			X(InX),
			Y(InY),
			Z(InZ)
		{
			MsgType = TEXT("geometry_msgs/Point");
		}

		// DEPRECATED! Will be removed when the generator is used again.
		Point(FVector InVector)
		{
			MsgType = "geometry_msgs/Point";
			X = InVector.X; Y = InVector.Y; Z = InVector.Z;
		}

		~Point() override {}

		// Getters 
		double GetX() const { return X; }
		double GetY() const { return Y; }
		double GetZ() const { return Z; }
		
		// DEPRECATED! Will be removed when the generator is used again.
		FVector GetVector() const
		{
			return FVector(X, Y, Z);
		}

		// Setters 
		void SetX(double InX) { X = InX; }
		void SetY(double InY) { Y = InY; }
		void SetZ(double InZ) { Z = InZ; }
		
		// DEPRECATED! Will be removed when the generator is used again.
		void SetVector(const FVector& InVector)
		{
			X = InVector.X; Y = InVector.Y; Z = InVector.Z;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			X = JsonObject->GetNumberField(TEXT("x"));

			Y = JsonObject->GetNumberField(TEXT("y"));

			Z = JsonObject->GetNumberField(TEXT("z"));

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			X = BsonObject->GetNumberField(TEXT("x"));

			Y = BsonObject->GetNumberField(TEXT("y"));

			Z = BsonObject->GetNumberField(TEXT("z"));

		}

		static Point GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Point Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static Point GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			Point Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetNumberField(TEXT("x"), X);

			Object->SetNumberField(TEXT("y"), Y);

			Object->SetNumberField(TEXT("z"), Z);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetNumberField(TEXT("x"), X);

			Object->SetNumberField(TEXT("y"), Y);

			Object->SetNumberField(TEXT("z"), Z);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			return TEXT("Point { x = ") + FString::SanitizeFloat(X) +
				TEXT(", y = ") + FString::SanitizeFloat(Y) +
				TEXT(", z = ") + FString::SanitizeFloat(Z) +
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