// Copyright 2017, Institute for Artificial Intelligence - University of Bremen
#include "IUROSBridge.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FUROSBridgeModule"
class FUROSBridge : public IUROSBridge
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FUROSBridge, UROSBridge )



void FUROSBridge::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FUROSBridge::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

DEFINE_LOG_CATEGORY(LogROS);
#undef LOCTEXT_NAMESPACE
