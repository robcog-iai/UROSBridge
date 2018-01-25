#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Polygon.h"

class FROSBridgeMsgGeometrymsgsPolygonStamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header; 
    FROSBridgeMsgGeometrymsgsPolygon polygon;

public:
    FROSBridgeMsgGeometrymsgsPolygonStamped()
    {
        Type = "geometry_msgs/PolygonStamped";
    }

    FROSBridgeMsgGeometrymsgsPolygonStamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsPolygon polygon_) :
        header(header_), polygon(polygon_)
    {
        Type = "geometry_msgs/PolygonStamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsPolygonStamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsPolygon GetPolygon() const
    {
        return polygon; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetPolygon(FROSBridgeMsgGeometrymsgsPolygon polygon_)
    {
        polygon = polygon_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        polygon = FROSBridgeMsgGeometrymsgsPolygon::GetFromJson(JsonObject->GetObjectField(TEXT("polygon")));
    }

    static FROSBridgeMsgGeometrymsgsPolygonStamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPolygonStamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("PolygonStamped { header = ") + header.ToString() + 
                     TEXT(", polygon = ") + polygon.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("polygon"), polygon.ToJsonObject());
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