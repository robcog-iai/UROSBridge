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
			Covariance.SetNumZeroed(36);
		}

		PoseWithCovariance
		(geometry_msgs::Pose InPose, const TArray<double>& InCovariance) :
			Pose(InPose), Covariance(InCovariance)
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

		void SetCovariance(const TArray<double>& InCovariance)
		{
			Covariance = InCovariance;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override 
		{
			Pose = geometry_msgs::Pose::GetFromJson(JsonObject->GetObjectField(TEXT("pose")));
			Covariance.Empty();
			TArray<TSharedPtr<FJsonValue>> CovariancePtrArr = JsonObject->GetArrayField(TEXT("covariance"));
			for (auto &ptr : CovariancePtrArr)
				Covariance.Add(ptr->AsNumber());

			check(Covariance.Num() == 36);
		}

		static PoseWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			PoseWithCovariance Result;
			Result.FromJson(JsonObject);
			return Result;
		}

		virtual FString ToString() const override
		{
			FString ArrayString = "[ ";
			for (auto &cov_value : Covariance)
				ArrayString += FString::SanitizeFloat(cov_value) + TEXT(", ");
			ArrayString += " ]";

			return TEXT("PoseWithCovariance { pose = ") + Pose.ToString() +
				TEXT(", covariance = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> CovArray;
			for (auto &val : Covariance)
				CovArray.Add(MakeShareable(new FJsonValueNumber(val)));

			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
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