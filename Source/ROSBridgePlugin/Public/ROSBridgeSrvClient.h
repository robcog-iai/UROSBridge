#pragma once

#include "Core.h"
#include "LogMacros.h"
#include "ThreadingBase.h"
#include "Queue.h"
#include "Json.h"

#include "ROSTime.h"
#include "ROSBridgeSrv.h"

class ROSBRIDGEPLUGIN_API FROSBridgeSrvClient {
private:
    FString Name; 
    FString Type; 

public:
    FROSBridgeSrvClient() {} 

    FROSBridgeSrvClient(FString Name_, FString Type_): Name(Name_), Type(Type_) { }

    FString GetName() const { return Name; }

    FString GetType() const { return Type; }
    
    virtual void CallBack(TSharedPtr<FROSBridgeSrv::SrvRequest> Request, TSharedPtr<FROSBridgeSrv::SrvResponse> Response)
    {
        // do something; 
    }
}; 