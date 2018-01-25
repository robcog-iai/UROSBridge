#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Accel.h"

class FROSBridgeMsgGeometrymsgsAccelWithCovariance : public FROSBridgeMsg
{
    FROSBridgeMsgGeometrymsgsAccel accel;

public:
    TArray<double> covariance;

    FROSBridgeMsgGeometrymsgsAccelWithCovariance()
    {
        Type = "geometry_msgs/AccelWithCovariance";
        covariance.SetNumZeroed(36);
    }

    FROSBridgeMsgGeometrymsgsAccelWithCovariance
    (FROSBridgeMsgGeometrymsgsAccel accel_, const TArray<double>& covariance_) :
        accel(accel_), covariance(covariance_)
    {
        Type = "geometry_msgs/AccelWithCovariance";
    }

    ~FROSBridgeMsgGeometrymsgsAccelWithCovariance() override {}

    FROSBridgeMsgGeometrymsgsAccel GetAccel() const
    {
        return accel;
    }

    TArray<double> GetCovariance() const
    {
        return covariance;
    }

    void SetAccel(FROSBridgeMsgGeometrymsgsAccel accel_)
    {
        accel = accel_;
    }

    void SetCovariance(const TArray<double>& covariance_)
    {
        covariance = covariance_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        accel = FROSBridgeMsgGeometrymsgsAccel::GetFromJson(JsonObject->GetObjectField(TEXT("accel")));
        covariance.Empty();
        TArray<TSharedPtr<FJsonValue>> CovariancePtrArr = JsonObject->GetArrayField(TEXT("covariance"));
        for (auto &ptr : CovariancePtrArr)
            covariance.Add(ptr->AsNumber());

        check(covariance.Num() == 36);
    }

    static FROSBridgeMsgGeometrymsgsAccelWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsAccelWithCovariance Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString() const override
    {
        FString ArrayString = "[ ";
        for (auto &cov_value : covariance)
            ArrayString += FString::SanitizeFloat(cov_value) + TEXT(", ");
        ArrayString += " ]";

        return TEXT("AccelWithCovariance { accel = ") + accel.ToString() +
            TEXT(", covariance = ") + ArrayString + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

        TArray<TSharedPtr<FJsonValue>> CovArray;
        for (auto &val : covariance)
            CovArray.Add(MakeShareable(new FJsonValueNumber(val)));

        Object->SetObjectField(TEXT("accel"), accel.ToJsonObject());
        Object->SetArrayField(TEXT("covariance"), CovArray);
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
	class AccelWithCovariance : public FROSBridgeMsg
	{
		geometry_msgs::Accel Accel;

	public:
		TArray<double> Covariance;

		AccelWithCovariance()
		{
			Type = "geometry_msgs/AccelWithCovariance";
			Covariance.SetNumZeroed(36);
		}

		AccelWithCovariance
		(geometry_msgs::Accel InAccel, const TArray<double>& InCovariance) :
			Accel(InAccel), Covariance(InCovariance)
		{
			Type = "geometry_msgs/AccelWithCovariance";
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
			for (auto &ptr : CovariancePtrArr)
				Covariance.Add(ptr->AsNumber());

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
			for (auto &cov_value : Covariance)
				ArrayString += FString::SanitizeFloat(cov_value) + TEXT(", ");
			ArrayString += " ]";

			return TEXT("AccelWithCovariance { accel = ") + Accel.ToString() +
				TEXT(", covariance = ") + ArrayString + TEXT(" } ");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override 
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

			TArray<TSharedPtr<FJsonValue>> CovArray;
			for (auto &val : Covariance)
				CovArray.Add(MakeShareable(new FJsonValueNumber(val)));

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