// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "Core.h"
#include "Json.h"

#include "ROSBridgeSrv.h"

class UROSBRIDGE_API FROSBridgeSrvClient {
protected:
    FString Name; 
    FString Type; 

public:
    FROSBridgeSrvClient() {} 

    FROSBridgeSrvClient(FString Name_, FString Type_): Name(Name_), Type(Type_) { }

    FString GetName() const { return Name; }

    FString GetType() const { return Type; }
    
    virtual void CallBack(TSharedPtr<FROSBridgeSrv::SrvRequest> Request, TSharedPtr<FROSBridgeSrv::SrvResponse> Response) const = 0;
}; 
