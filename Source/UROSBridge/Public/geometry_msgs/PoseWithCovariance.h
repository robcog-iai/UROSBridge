#pragma once

#include "ROSBridgeMsg.h"

#include "geometry_msgs/Pose.h"

namespace geometry_msgs
{
	class PoseWithCovariance : public FROSBridgeMsg
	{
		geometry_msgs::Pose Pose;
		TArray<double> Covariance;
	public:
		PoseWithCovariance()
		{
			MsgType = "geometry_msgs/PoseWithCovariance";
		}

		PoseWithCovariance
		(
			geometry_msgs::Pose InPose,
			const TArray<double>& InCovariance
		):
			Pose(InPose),
			Covariance(InCovariance)
		{
			MsgType = "geometry_msgs/PoseWithCovariance";
		}

		~PoseWithCovariance() override {}

		geometry_msgs::Pose GetPose() const
		{
			return Pose;
		}

		TArray<double> GetCovariance() const
		{
			return Covariance;
		}

		void SetPose(geometry_msgs::Pose InPose)
		{
			Pose = InPose;
		}

		void SetCovariance(TArray<double>& InCovariance)
		{
			Covariance = InCovariance;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Pose = geometry_msgs::Pose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));

			TArray<TSharedPtr<FJsonValue>> ValuesPtrArr;

			Covariance.Empty();
			ValuesPtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		virtual void FromBson(TSharedPtr<FBsonObject> BsonObject) override
		{
			Pose = geometry_msgs::Pose::GetFromBson(BsonObject->GetObjectField(TEXT("pose")));

			TArray<TSharedPtr<FBsonValue>> ValuesPtrArr;

			Covariance.Empty();
			ValuesPtrArr = BsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : ValuesPtrArr)
				Covariance.Add(ptr->AsNumber());

		}

		static PoseWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseWithCovariance Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		static PoseWithCovariance GetFromBson(TSharedPtr<FBsonObject> BsonObject)
		{
			PoseWithCovariance Result;
			Result.FromBson(BsonObject);
			return Result;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
			TArray<TSharedPtr<FJsonValue>> CovarianceArray;
			for (auto &val : Covariance)
				CovarianceArray.Add(MakeShareable(new FJsonValueNumber(val)));
			Object->SetArrayField(TEXT("covariance"), CovarianceArray);
			return Object;
		}
		virtual TSharedPtr<FBsonObject> ToBsonObject() const override
		{
			TSharedPtr<FBsonObject> Object = MakeShareable<FBsonObject>(new FBsonObject());

			Object->SetObjectField(TEXT("pose"), Pose.ToBsonObject());
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