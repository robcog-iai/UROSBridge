#pragma once
#include "ROSBridgeMsg.h"

#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

class FROSBridgeMsgGeometrymsgsVector3Stamped : public FROSBridgeMsg
{
    FROSBridgeMsgStdmsgsHeader header; 
    FROSBridgeMsgGeometrymsgsVector3 vector;

public:
    FROSBridgeMsgGeometrymsgsVector3Stamped()
    {
        Type = "geometry_msgs/Vector3Stamped";
    }

    FROSBridgeMsgGeometrymsgsVector3Stamped
    (FROSBridgeMsgStdmsgsHeader header_, FROSBridgeMsgGeometrymsgsVector3 vector_) :
        header(header_), vector(vector_)
    {
        Type = "geometry_msgs/Vector3Stamped";
    }
    
    ~FROSBridgeMsgGeometrymsgsVector3Stamped() override {}

    FROSBridgeMsgStdmsgsHeader GetHeader() const 
    {
        return header; 
    }

    FROSBridgeMsgGeometrymsgsVector3 GetVector() const
    {
        return vector; 
    }

    void SetHeader(FROSBridgeMsgStdmsgsHeader header_)
    {
        header = header_; 
    }

    void SetVector(FROSBridgeMsgGeometrymsgsVector3 vector_)
    {
        vector = vector_;
    }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        header = FROSBridgeMsgStdmsgsHeader::GetFromJson(JsonObject->GetObjectField(TEXT("header")));
        vector = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("vector")));
    }

    static FROSBridgeMsgGeometrymsgsVector3Stamped GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsVector3Stamped Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Vector3Stamped { header = ") + header.ToString() + 
                     TEXT(", vector = ") + vector.ToString() + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetObjectField(TEXT("header"), header.ToJsonObject());
        Object->SetObjectField(TEXT("vector"), vector.ToJsonObject());
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
