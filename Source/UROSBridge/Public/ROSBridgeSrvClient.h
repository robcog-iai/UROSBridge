// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "Core.h"
#include "Json.h"

#include "ROSBridgeSrv.h"

class UROSBRIDGE_API FROSBridgeSrvClient 
{
protected:
    FString Name; 
    FString Type; 

public:
    FROSBridgeSrvClient() 
	{
	} 

	virtual ~FROSBridgeSrvClient() 
	{
	}

    FROSBridgeSrvClient(FString InName, FString InType): Name(InName), Type(InType) 
	{
	}

    FString GetName() const 
	{ 
		return Name; 
	}

    FString GetType() const 
	{ 
		return Type; 
	}
    
    virtual void Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest, TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse) = 0;
}; 
