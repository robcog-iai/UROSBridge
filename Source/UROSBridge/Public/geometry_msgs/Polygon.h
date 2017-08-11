#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Point32.h"

class FROSBridgeMsgGeometrymsgsPolygon : public FROSBridgeMsg
{
public:
    TArray<FROSBridgeMsgGeometrymsgsPoint32> points; 

    FROSBridgeMsgGeometrymsgsPolygon()
    {
        Type = "geometry_msgs/Polygon";
    }

    FROSBridgeMsgGeometrymsgsPolygon
    (const TArray<FROSBridgeMsgGeometrymsgsPoint32>& points_) 
    {
        Type = "geometry_msgs/Polygon";
        for (int i = 0; i < points_.Num(); i++)
        {
            points.Add(points_[i]); 
        }
    }
    
    ~FROSBridgeMsgGeometrymsgsPolygon() override {}

    TArray<FROSBridgeMsgGeometrymsgsPoint32> GetPoints() const
    {
        return points; 
    }

    FROSBridgeMsgGeometrymsgsPoint32 GetPointAt(uint32 Index)
    {
        check(Index < points.Num()); 
        return points[Index]; 
    }

    void AddPoint(FROSBridgeMsgGeometrymsgsPoint32 point)
    {
        points.Add(point); 
    }

    void SetPoints(const TArray<FROSBridgeMsgGeometrymsgsPoint32>& points_)
    {
        for (int i = 0; i < points_.Num(); i++)
        {
            points.Add(points_[i]);
        }
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        TArray<TSharedPtr<FJsonValue>> PointsPtrArray = JsonObject->GetArrayField(TEXT("points")); 
        for (auto &ptr : PointsPtrArray)
        {
            FROSBridgeMsgGeometrymsgsPoint32 point =
                FROSBridgeMsgGeometrymsgsPoint32::GetFromJson(ptr->AsObject()); 
            points.Add(point); 
        }
    }

    static FROSBridgeMsgGeometrymsgsPolygon GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsPolygon Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        FString ArrayString = "[ "; 
        for (auto &point : points)
            ArrayString += point.ToString() + TEXT(", "); 
        ArrayString += " ]"; 

        return TEXT("Polygon { points = ") + ArrayString + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        TArray<TSharedPtr<FJsonValue>> PointsPtrArray; 
        for (auto &point : points)
        {
            TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(point.ToJsonObject())); 
            PointsPtrArray.Add(Ptr);
        } 

        Object->SetArrayField("points", PointsPtrArray); 
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
