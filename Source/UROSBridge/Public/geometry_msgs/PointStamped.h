#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Point.h"

class FROSBridgeMsgGeometrymsgsPointStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header; 
    FROSBridgeMsgGeometrymsgsPoint point;

public:
    FROSBridgeMsgGeometrymsgsPointStamped()
    {
        MsgType = "geometry_msgs/PointStamped";
    }

    FROSBridgeMsgGeometrymsgsPointStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsPoint point_) :
        header(header_), point(point_)
    {
        MsgType = "geometry_msgs/PointStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsPointStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsPoint GetPoint() const
    {
        return point; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetPoint(FROSBridgeMsgGeometrymsgsPoint point_)
    {
        point = point_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        point = FROSBridgeMsgGeometrymsgsPoint::GetFromJson(JsonObject->GetObjectField(TEXT("point")));
    }

    static FROSBridgeMsgGeometrymsgsPointStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPointStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("PointStamped { header = ") + header.ToString() + 
                     TEXT(", point = ") + point.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("point"), point.ToJsonObject());
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