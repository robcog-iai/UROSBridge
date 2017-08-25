#pragma once

#include "ROSBridgeSrvClient.h"
#include "tutorial_srvs/AddTwoInts.h"

class FROSAddTwoIntsClient final : public FROSBridgeSrvClient
{
public:
    FROSAddTwoIntsClient(FString Name):
        FROSBridgeSrvClient(Name, TEXT("beginner_tutorials/AddTwoInts"))
    {

    }

    void CallBack(TSharedPtr<FROSBridgeSrv::SrvRequest> Request, TSharedPtr<FROSBridgeSrv::SrvResponse> Response) const override
    {
        TSharedPtr<FROSBridgeSrvRospytutorialsAddTwoInts::Request> Request_ =
            StaticCastSharedPtr<FROSBridgeSrvRospytutorialsAddTwoInts::Request>(Request);
        TSharedPtr<FROSBridgeSrvRospytutorialsAddTwoInts::Response> Response_=
            StaticCastSharedPtr<FROSBridgeSrvRospytutorialsAddTwoInts::Response>(Response);
        UE_LOG(LogTemp, Log, TEXT("Add Two Ints: %d + %d = %d"), Request_->GetA(), Request_->GetB(), Response_->GetSum());
    }
};
