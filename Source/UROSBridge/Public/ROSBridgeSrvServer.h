// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "Core.h"
#include "Json.h"
#include "UROSBridge.h"

#include "ROSBridgeSrv.h"


class UROSBRIDGE_API FROSBridgeSrvServer
{
protected:
	FString Name;
	FString Type;

public:
	FROSBridgeSrvServer() 
	{
	}

	FROSBridgeSrvServer(FString InName, FString InType):
		Name(InName), Type(InType)
	{
	}

	virtual ~FROSBridgeSrvServer() 
	{
	}

	FString GetType() const 
	{
		return Type; 
	}

	FString GetName() const 
	{
		return Name;
	}

	virtual TSharedPtr<FROSBridgeSrv::SrvRequest> FromJson(TSharedPtr<FJsonObject> JsonObject) const = 0;
	
	virtual TSharedPtr<FROSBridgeSrv::SrvRequest> FromBson(TSharedPtr<FBsonObject> BsonObject) const {
		UE_LOG(LogROS, Warning, TEXT("Empty SrvRequest created. Did you forget to overwrite FromBson()?"));
		return MakeShareable(new FROSBridgeSrv::SrvRequest());
	}

	virtual TSharedPtr<FROSBridgeSrv::SrvResponse> Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest) = 0;
}; 
