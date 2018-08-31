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
			MsgType = TEXT("geometry_msgs/TwistWithCovariance");
		}
		
		TwistWithCovariance(geometry_msgs::Twist InTwist,
			TArray<double> InCovariance)
			:
			Twist(InTwist),
			Covariance(InCovariance)
		{
			MsgType = TEXT("geometry_msgs/TwistWithCovariance");
		}

		~TwistWithCovariance() override {}

		// Getters 
		geometry_msgs::Twist GetTwist() const { return Twist; }
		TArray<double> GetCovariance() const { return Covariance; }

		// Setters 
		void SetTwist(geometry_msgs::Twist InTwist) { Twist = InTwist; }
		void SetCovariance(TArray<double> InCovariance) { Covariance = InCovariance; }

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Twist = geometry_msgs::Twist::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));

			Covariance.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Twist = geometry_msgs::Twist::GetFromBson(BsonObject->GetObjectField(TEXT("twist")));

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

		virtual FString ToString() const override
		{
							
			FString CovarianceString = "[ ";
			for (auto &value : Covariance)
				CovarianceString += FString::SanitizeFloat(value) + TEXT(", ");
			CovarianceString += " ] ";
			return TEXT("TwistWithCovariance { twist = ") + Twist.ToString() +
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