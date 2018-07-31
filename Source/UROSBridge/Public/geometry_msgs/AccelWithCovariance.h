#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/Accel.h"

namespace geometry_msgs
{
	class AccelWithCovariance : public FROSBridgeMsg
	{
		geometry_msgs::Accel Accel;
		TArray<double> Covariance;
	public:
		AccelWithCovariance()
		{
			MsgType = "geometry_msgs/AccelWithCovariance";
		}

		AccelWithCovariance
		(
			geometry_msgs::Accel InAccel,
			const TArray<double>& InCovariance
		):
			Accel(InAccel),
			Covariance(InCovariance)
		{
			MsgType = "geometry_msgs/AccelWithCovariance";
		}

		~AccelWithCovariance() override {}

		geometry_msgs::Accel GetAccel() const
		{
			return Accel;
		}

		TArray<double> GetCovariance() const
		{
			return Covariance;
		}

		void SetAccel(geometry_msgs::Accel InAccel)
		{
			Accel = InAccel;
		}

		void SetCovariance(TArray<double>& InCovariance)
		{
			Covariance = InCovariance;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Accel = geometry_msgs::Accel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Covariance.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Accel = geometry_msgs::Accel::GetFromBson(BsonObject->GetObjectField(TEXT("accel")));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

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
		virtual FString ToYamlString() const override
		{
			FString OutputString;
			TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
			FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
			return OutputString;
		}
	};
}