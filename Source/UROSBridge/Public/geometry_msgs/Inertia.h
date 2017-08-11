#pragma once
#include "ROSBridgeMsg.h"

#include "geometry_msgs/Vector3.h"

class FROSBridgeMsgGeometrymsgsInertia : public FROSBridgeMsg
{
    double m; 
    FROSBridgeMsgGeometrymsgsVector3 com;
    double ixx, ixy, ixz, iyy, iyz, izz; 

public:
    FROSBridgeMsgGeometrymsgsInertia()
    {
        Type = "geometry_msgs/Inertia";
    }

    FROSBridgeMsgGeometrymsgsInertia
    (double m_, FROSBridgeMsgGeometrymsgsVector3 com_, 
        double ixx_, double ixy_, double ixz_, double iyy_, double iyz_, double izz_) :
        m(m_), com(com_), ixx(ixx_), ixy(ixy_), ixz(ixz_), iyy(iyy_), iyz(iyz_), izz(izz_) 
    {
        Type = "geometry_msgs/Inertia";
    }
    
    ~FROSBridgeMsgGeometrymsgsInertia() override {}

    FROSBridgeMsgGeometrymsgsVector3 GetCom() const
    {
        return com; 
    }

    double GetM() const { return m; }
    double GetIxx() const { return ixx; }
    double GetIxy() const { return ixy; }
    double GetIxz() const { return ixz; }
    double GetIyy() const { return iyy; }
    double GetIyz() const { return iyz; }
    double GetIzz() const { return izz; }

    void SetCom(FROSBridgeMsgGeometrymsgsVector3 com_)
    {
        com = com_; 
    }

    void SetM(double m_) { m = m_; }
    void SetIxx(double ixx_) { ixx = ixx_; }
    void SetIxy(double ixy_) { ixy = ixy_; }
    void SetIxz(double ixz_) { ixz = ixz_; }
    void SetIyy(double iyy_) { iyy = iyy_; }
    void SetIyz(double iyz_) { iyz = iyz_; }
    void SetIzz(double izz_) { izz = izz_; }

    virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override {
        m = JsonObject->GetNumberField(TEXT("m")); 
        com = FROSBridgeMsgGeometrymsgsVector3::GetFromJson(JsonObject->GetObjectField(TEXT("com")));
        ixx = JsonObject->GetNumberField(TEXT("ixx"));
        ixy = JsonObject->GetNumberField(TEXT("ixy"));
        ixz = JsonObject->GetNumberField(TEXT("ixz"));
        iyy = JsonObject->GetNumberField(TEXT("iyy"));
        iyz = JsonObject->GetNumberField(TEXT("iyz"));
        izz = JsonObject->GetNumberField(TEXT("izz"));
    }

    static FROSBridgeMsgGeometrymsgsInertia GetFromJson(TSharedPtr<FJsonObject> JsonObject)
    {
        FROSBridgeMsgGeometrymsgsInertia Result;
        Result.FromJson(JsonObject); 
        return Result; 
    }

    virtual FString ToString () const override
    {
        return TEXT("Inertia { m = ") + FString::SanitizeFloat(m) + 
                     TEXT(", com = ") + com.ToString() + 
                     TEXT(", ixx = ") + FString::SanitizeFloat(ixx) + 
                     TEXT(", ixy = ") + FString::SanitizeFloat(ixy) +
                     TEXT(", ixz = ") + FString::SanitizeFloat(ixz) +
                     TEXT(", iyy = ") + FString::SanitizeFloat(iyy) +
                     TEXT(", iyz = ") + FString::SanitizeFloat(iyz) +
                     TEXT(", izz = ") + FString::SanitizeFloat(izz) + TEXT(" } ");
    }

    virtual TSharedPtr<FJsonObject> ToJsonObject() const override {
        TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
        Object->SetNumberField(TEXT("m"), m); 
        Object->SetObjectField(TEXT("com"), com.ToJsonObject());
        Object->SetNumberField(TEXT("ixx"), ixx);
        Object->SetNumberField(TEXT("ixy"), ixy);
        Object->SetNumberField(TEXT("ixz"), ixz);
        Object->SetNumberField(TEXT("iyy"), iyy);
        Object->SetNumberField(TEXT("iyz"), iyz);
        Object->SetNumberField(TEXT("izz"), izz);
        return Object;
    }

    virtual FString ToYamlString() const override {
        FString OutputString; 
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
        FJsonSerializer::Serialize(ToJsonObject().ToSharedRef(), Writer);
        return OutputString;
    }
};
