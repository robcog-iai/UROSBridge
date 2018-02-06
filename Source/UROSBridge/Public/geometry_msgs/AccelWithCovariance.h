#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Accel.h"

namespace geometry_msgs
{
	class AccelWithCovariance : public FROSBridgeMsg
	{
		geometry_msgs::Accel Accel;

	public:
		TArray<double> Covariance;

		AccelWithCovariance()
		{
			MsgType = "geometry_msgs/AccelWithCovariance";
			Covariance.SetNumZeroed(36);
		}

		AccelWithCovariance
		(geometry_msgs::Accel InAccel, const TArray<double>& InCovariance) :
			Accel(InAccel), Covariance(InCovariance)
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

		void SetCovariance(const TArray<double>& InCovariance)
		{
			Covariance = InCovariance;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Accel = geometry_msgs::Accel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));
			Covariance.Empty();
			TArray<TSharedPtr<FJsonValue>> CovariancePtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &Cov : CovariancePtrArr)
			{
				Covariance.Add(Cov->AsNumber());
			}

			check(Covariance.Num() == 36);
		}

		static AccelWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			AccelWithCovariance Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayString = "[ ";
			for (auto &Val : Covariance)
			{
				ArrayString += FString::SanitizeFloat(Val) + TEXT(", ");
			}
			ArrayString += " ]";

			return TEXT("AccelWithCovariance { accel = ") + Accel.ToString() +
				TEXT(", covariance = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> CovArray;
			for (auto &Val : Covariance)
			{
				CovArray.Add(MakeShareable(new FJsonValueNumber(Val)));
			}

			Object->SetObjectField(TEXT("accel"), Accel.ToJsonObject());
			Object->SetArrayField(TEXT("covariance"), CovArray);
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