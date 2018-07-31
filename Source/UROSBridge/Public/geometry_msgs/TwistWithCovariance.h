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
		}

		TwistWithCovariance
		(
			geometry_msgs::Twist InTwist,
			const TArray<double>& InCovariance
		):
			Twist(InTwist),
			Covariance(InCovariance)
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

		void SetCovariance(TArray<double>& InCovariance)
		{
			Covariance = InCovariance;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Twist = geometry_msgs::Twist::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Covariance.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Twist = geometry_msgs::Twist::GetFromBson(BsonObject->GetObjectField(TEXT("twist")));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Covariance.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		static TwistWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			TwistWithCovariance Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static TwistWithCovariance GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			TwistWithCovariance Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("twist"), Twist.ToJsonObject());
			TArray<TSharedPtr<FJsonValue>> CovarianceArray;
			for (auto &val : Covariance)
				CovarianceArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("covariance"), CovarianceArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("twist"), Twist.ToBsonObject());
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