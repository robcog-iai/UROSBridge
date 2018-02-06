#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Twist.h"

namespace geometry_msgs
{
	class TwistWithCovariance : public FROSBridgeMsg
	{
		geometry_msgs::Twist Twist;
		TArray<double> Covariance;

	public:
		TwistWithCovariance()
		{
			MsgType = "geometry_msgs/TwistWithCovariance";
			Covariance.SetNumZeroed(36);
		}

		TwistWithCovariance
		(geometry_msgs::Twist InTwist, const TArray<double>& InCovariance) :
			Twist(InTwist), Covariance(InCovariance)
		{
			MsgType = "geometry_msgs/TwistWithCovariance";
		}

		~TwistWithCovariance() override {}

		geometry_msgs::Twist GetTwist() const
		{
			return Twist;
		}

		TArray<double> GetCovariance() const
		{
			return Covariance;
		}

		void SetTwist(geometry_msgs::Twist InTwist)
		{
			Twist = InTwist;
		}

		void SetCovariance(const TArray<double>& InCovariance)
		{
			Covariance = InCovariance;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Twist = geometry_msgs::Twist::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));
			Covariance.Empty();
			TArray<TSharedPtr<FJsonValue>> CovariancePtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : CovariancePtrArr)
				Covariance.Add(ptr->AsNumber());

			check(Covariance.Num() == 36);
		}

		static TwistWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TwistWithCovariance Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayString = "[ ";
			for (auto &cov_value : Covariance)
				ArrayString += FString::SanitizeFloat(cov_value) + TEXT(", ");
			ArrayString += " ]";

			return TEXT("TwistWithCovariance { twist = ") + Twist.ToString() +
				TEXT(", covariance = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> CovArray;
			for (auto &val : Covariance)
				CovArray.Add(MakeShareable(new FJsonValueNumber(val)));

			Object->SetObjectField(TEXT("twist"), Twist.ToJsonObject());
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