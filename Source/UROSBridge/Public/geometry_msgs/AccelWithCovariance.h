#pragma once

#include "ROSBridgeMsg.h"
#include "geometry_msgs/Accel.h"


namespace geometry_msgs
{
	class AccelWithCovariance : public FROSBridgeMsg
	{
		geometry_msgs::Accel Accel;
	public:
		// WARNING! Will be private when the generator is used again. Use Getters and Setters instead of direct access.
		TArray<double> Covariance;
		
		AccelWithCovariance()
		{
			MsgType = TEXT("geometry_msgs/AccelWithCovariance");
		}
		
		AccelWithCovariance(geometry_msgs::Accel InAccel,
			TArray<double> InCovariance)
			:
			Accel(InAccel),
			Covariance(InCovariance)
		{
			MsgType = TEXT("geometry_msgs/AccelWithCovariance");
		}

		~AccelWithCovariance() override {}

		// Getters 
		geometry_msgs::Accel GetAccel() const { return Accel; }
		TArray<double> GetCovariance() const { return Covariance; }

		// Setters 
		void SetAccel(geometry_msgs::Accel InAccel) { Accel = InAccel; }
		void SetCovariance(TArray<double> InCovariance) { Covariance = InCovariance; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Accel = geometry_msgs::Accel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));

			Covariance.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Accel = geometry_msgs::Accel::GetFromBson(BsonObject->GetObjectField(TEXT("accel")));

			Covariance.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		static AccelWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			AccelWithCovariance Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static AccelWithCovariance GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			AccelWithCovariance Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("accel"), Accel.ToJsonObject());

			TArray<TSharedPtr<FJsonValue>> CovarianceArray;
			for (auto &val : Covariance)
				CovarianceArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("covariance"), CovarianceArray);

			return Object;

		}

		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("accel"), Accel.ToBsonObject());

			TArray<TSharedPtr<FBsonValue>> CovarianceArray;
			for (auto &val : Covariance)
				CovarianceArray.Add(MakeShareable(new FBsonValueNumber(val)));
			Object->SetArrayField(TEXT("covariance"), CovarianceArray);

			return Object;

		}

		virtual FString ToString() const override
		{
							
			FString CovarianceString = "[ ";
			for (auto &value : Covariance)
				CovarianceString += FString::SanitizeFloat(value) + TEXT(", ");
			CovarianceString += " ] ";
			return TEXT("AccelWithCovariance { accel = ") + Accel.ToString() +
				TEXT(", covariance =") + CovarianceString +
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