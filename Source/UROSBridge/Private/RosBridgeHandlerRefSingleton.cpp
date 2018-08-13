// Fill out your copyright notice in the Description page of Project Settings.

#include "RosBridgeHandlerRefSingleton.h"



TSharedPtr<FROSBridgeHandler> URosBridgeHandlerRefSingleton::GetHandlerRef()
{
	if (Handler.IsValid())
		return Handler;

	Handler = MakeShareable<FROSBridgeHandler>(
		new FROSBridgeHandler(TEXT("127.0.0.1"), 9090));
	return Handler;

}

