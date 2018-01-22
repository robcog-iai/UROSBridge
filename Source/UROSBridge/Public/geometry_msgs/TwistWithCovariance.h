#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Twist.h"

class FROSBridgeMsgGeometrymsgsTwistWithCovariance : public FROSBridgeMsg
{
    FROSBridgeMsgGeometrymsgsTwist twist;

public:
    TArray<double> covariance;

    FROSBridgeMsgGeometrymsgsTwistWithCovariance()
    {
        Type = "geometry_msgs/TwistWithCovariance";
        covariance.SetNumZeroed(36);
    }

    FROSBridgeMsgGeometrymsgsTwistWithCovariance
    (FROSBridgeMsgGeometrymsgsTwist twist_, const TArray<double>& covariance_) :
        twist(twist_), covariance(covariance_)
    {
        Type = "geometry_msgs/TwistWithCovariance";
    }

    ~FROSBridgeMsgGeometrymsgsTwistWithCovariance() override {}

    FROSBridgeMsgGeometrymsgsTwist GetTwist() const
    {
        return twist;
    }

    TArray<double> GetCovariance() const
    {
        return covariance;
    }

    void SetTwist(FROSBridgeMsgGeometrymsgsTwist twist_)
    {
        twist = twist_;
    }

    void SetCovariance(const TArray<double>& covariance_)
    {
        covariance = covariance_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        twist = FROSBridgeMsgGeometrymsgsTwist::GetFromJson(JsonObject->GetObjectField(TEXT("twist")));
        covariance.Empty();
        TArray<TSharedPtr<FJsonValue>> CovariancePtrArr = JsonObject->GetArrayField(TEXT("covariance"));
        for (auto &ptr : CovariancePtrArr)
            covariance.Add(ptr->AsNumber());

        check(covariance.Num() == 36);
    }

    static FROSBridgeMsgGeometrymsgsTwistWithCovariance GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsTwistWithCovariance Result;
        Result.FromJson(JsonObject);
        return Result;
    }

    virtual FString ToString() const override
    {
        FString ArrayString = "[ ";
        for (auto &cov_value : covariance)
            ArrayString += FString::SanitizeFloat(cov_value) + TEXT(", ");
        ArrayString += " ]";

        return TEXT("TwistWithCovariance { twist = ") + twist.ToString() +
            TEXT(", covariance = ") + ArrayString + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());

        TArray<TSharedPtr<FJsonValue>> CovArray;
        for (auto &val : covariance)
            CovArray.Add(MakeShareable(new FJsonValueNumber(val)));

        Object->SetObjectField(TEXT("twist"), twist.ToJsonObject());
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
} // namespace geometry_msgs