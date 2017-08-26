#pragma once

#include "ROSBridgeSrvServer.h"
#include "tutorial_srvs/AddTwoInts.h"

class FROSAddTwoIntsServer final : public FROSBridgeSrvServer
{
public:
    FROSAddTwoIntsServer(FString Name):
        FROSBridgeSrvServer(Name, TEXT("beginner_tutorials/AddTwoInts"))
    {

    }

    TSharedPtr<FROSBridgeSrv::SrvRequest> FromJson(TSharedPtr<FJsonObject> JsonObject) const override
    {
        TSharedPtr<FROSBridgeSrvRospytutorialsAddTwoInts::Request> Request_ =
            MakeShareable(new FROSBridgeSrvRospytutorialsAddTwoInts::Request());
        Request_->FromJson(JsonObject);
        return TSharedPtr<FROSBridgeSrv::SrvRequest>(Request_);
    }

    TSharedPtr<FROSBridgeSrv::SrvResponse> CallBack(TSharedPtr<FROSBridgeSrv::SrvRequest> Request) const override
    {
        TSharedPtr<FROSBridgeSrvRospytutorialsAddTwoInts::Request> Request_ =
            StaticCastSharedPtr<FROSBridgeSrvRospytutorialsAddTwoInts::Request>(Request);

        int64 Sum = Request_->GetA() + Request_->GetB();
        UE_LOG(LogTemp, Log, TEXT("Service [%s] Server: Add Two Ints: %d + %d = %d"), *Name, Request_->GetA(), Request_->GetB(), Sum);

        return MakeShareable<FROSBridgeSrv::SrvResponse>
                (new FROSBridgeSrvRospytutorialsAddTwoInts::Response(Sum));
    }
};
