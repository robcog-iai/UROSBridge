// Copyright 2017, Institute for Artificial Intelligence - University of Bremen


#include "UROSBridge.h"

#define LOCTEXT_NAMESPACE "FUROSBridgeModule"

void FUROSBridgeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUROSBridgeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUROSBridgeModule, UROSBridge)
DEFINE_LOG_CATEGORY(LogROS);