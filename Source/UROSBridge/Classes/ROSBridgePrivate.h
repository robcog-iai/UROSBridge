// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Modules/ModuleManager.h"

class FROSWebSocket; 
class FWebSocketServer; 
class FROSBridgeHandler;

typedef struct lws_context WebSocketInternalContext;
typedef struct lws WebSocketInternal;
typedef struct lws_protocols WebSocketInternalProtocol;

DECLARE_DELEGATE_TwoParams(FROSWebsocketPacketRecievedSignature, void* /*Data*/, int32 /*Data Size*/);
DECLARE_DELEGATE_OneParam(FROSWebsocketClientConnectedSignature, FROSWebSocket* /*Socket*/);
DECLARE_MULTICAST_DELEGATE(FROSWebsocketInfoSignature);
