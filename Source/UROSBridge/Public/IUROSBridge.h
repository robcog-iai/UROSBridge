// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

/* #include "Engine.h"
#include "Core.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgeMsg.h"
#include "WebSocket.h"
#include "WebSocketServer.h" */

/**
 * The public interface to this module
 */
class IUROSBridge : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IUROSBridge& Get()
	{
		return FModuleManager::LoadModuleChecked< IUROSBridge >( "UROSBridge" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "UROSBridge" );
	}
};

DECLARE_LOG_CATEGORY_EXTERN(LogROS, Log, All);

