// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#include "ROSBridgeHandler.h"
#include "UROSBridge.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Networking.h"
#include "Json.h"

void FROSBridgeHandler::OnConnection()
{
    UE_LOG(LogROS, Log, TEXT("[%s] Websocket server connected."), *FString(__FUNCTION__));

    SetClientConnected(true);
}

static void OnError()
{
    UE_LOG(LogROS, Error, TEXT("[%s] Error in Websocket."), *FString(__FUNCTION__));
}

// Create connection, bind functions to WebSocket Client, and Connect.
bool FROSBridgeHandler::FROSBridgeHandlerRunnable::Init()
{
#if UE_BUILD_DEBUG
    UE_LOG(LogROS, Log, TEXT("[%s]"), *FString(__FUNCTION__));
#endif

    FIPv4Address IPAddress;
    FIPv4Address::Parse(Handler->GetHost(), IPAddress);

    FIPv4Endpoint Endpoint(IPAddress, Handler->GetPort());
    Handler->Client = MakeShareable<FWebSocket>(new FWebSocket(Endpoint.ToInternetAddr().Get()));

    // Bind Received callback
    FWebsocketPacketRecievedCallBack ReceivedCallback;
    ReceivedCallback.BindRaw(this->Handler, &FROSBridgeHandler::OnMessage);
    Handler->Client->SetRecieveCallBack(ReceivedCallback);

    // Bind Connected callback
    FWebsocketInfoCallBack ConnectedCallback;
    ConnectedCallback.BindRaw(this->Handler, &FROSBridgeHandler::OnConnection);
    Handler->Client->SetConnectedCallBack(ConnectedCallback);

    // Bind Error callback
    FWebsocketInfoCallBack ErrorCallback;
    ErrorCallback.BindStatic(&OnError);
    Handler->Client->SetErrorCallBack(ErrorCallback);

    Handler->Client->Connect();

    return true;
}

// Process subscribed messages
uint32 FROSBridgeHandler::FROSBridgeHandlerRunnable::Run()
{
	//Initial wait before starting
	FPlatformProcess::Sleep(0.01);

	// Counter for re-trying an initially unsuccessful connection
	uint32 ConnectionTrialCounter = 0;

	// Main loop for the thread
	while (StopCounter.GetValue() == 0)
	{
		if (Handler->Client.IsValid() && !Handler->Client->IsDestroyed)
		{
			Handler->Client->Tick();
		}

		if (!Handler->IsClientConnected())
		{
			// We aren't yet connected

			if (++ConnectionTrialCounter > 100)
			{
				Stop();

				UE_LOG(LogROS, Error, TEXT("[%s] Could not connect to the rosbridge server (IP %s, port %d)!"),
					*FString(__FUNCTION__),
					*(Handler->GetHost()),
					Handler->GetPort());

				continue;
			}
		}
		else
		{
			// We are running and connected

			// Process any pending subsribers, publishers and service servers

			// Subscribe all pending topics
			while (Handler->ListPendingSubscribers.Num() > 0)
			{
				auto Subscriber = Handler->ListPendingSubscribers.Pop();
				UE_LOG(LogROS, Warning, TEXT("[%s] Subscribing Topic %s"), *FString(__FUNCTION__), *Subscriber->GetTopic());
				FString WebSocketMessage = FROSBridgeMsg::Subscribe(Subscriber->GetTopic(), Subscriber->GetType());
				Handler->Client->Send(WebSocketMessage);

				Handler->ListSubscribers.Push(Subscriber);
			}

			// Advertise all pending topics
			while (Handler->ListPendingPublishers.Num() > 0)
			{
				auto Publisher = Handler->ListPendingPublishers.Pop();
				UE_LOG(LogROS, Warning, TEXT("[%s] Advertising Topic %s"), *FString(__FUNCTION__), *Publisher->GetTopic());
				FString WebSocketMessage = FROSBridgeMsg::Advertise(Publisher->GetTopic(), Publisher->GetType());
				Handler->Client->Send(WebSocketMessage);

				Handler->ListPublishers.Push(Publisher);
			}

			// Advertise all pending service servers
			while (Handler->ListPendingServiceServers.Num() > 0)
			{
				auto ServiceServer = Handler->ListPendingServiceServers.Pop();
				UE_LOG(LogROS, Warning, TEXT("[%s] Advertising Service [%s] of type [%s]"),
					*FString(__FUNCTION__), *ServiceServer->GetName(), *ServiceServer->GetType());
				FString WebSocketMessage = FROSBridgeSrv::AdvertiseService(ServiceServer->GetName(), ServiceServer->GetType());
				Handler->Client->Send(WebSocketMessage);

				Handler->ListServiceServers.Push(ServiceServer);
			}

		}

		// Sleep the main loop
		FPlatformProcess::Sleep(Handler->GetClientInterval());
	}

    return 0;
}

// Set the stop counter and disconnect
void FROSBridgeHandler::FROSBridgeHandlerRunnable::Stop()
{
    StopCounter.Increment();
}


// Callback function when message comes from WebSocket
void FROSBridgeHandler::OnMessage(void* InData, int32 InLength)
{
    char * CharMessage = new char [InLength + 1];
    memcpy(CharMessage, InData, InLength);
    CharMessage[InLength] = 0;
    FString JsonMessage = UTF8_TO_TCHAR(CharMessage);
    delete[] CharMessage;

#if UE_BUILD_DEBUG
    UE_LOG(LogROS, Error, TEXT("[%s] Json Message: %s"), *FString(__FUNCTION__), *JsonMessage);
#endif

    // Parse Json Message Here
    TSharedRef< TJsonReader<> > Reader =
            TJsonReaderFactory<>::Create(JsonMessage);
    TSharedPtr< FJsonObject > JsonObject;
    bool DeserializeState = FJsonSerializer::Deserialize(Reader, JsonObject);
    if (!DeserializeState)
    {
        UE_LOG(LogROS, Error, TEXT("[%s] Deserialization Error. Message Contents: %s"),
			*FString(__FUNCTION__), *JsonMessage);
        return;
    }

    FString Op = JsonObject->GetStringField(TEXT("op"));

    if (Op == TEXT("publish")) // Message 
    {
        FString Topic = JsonObject->GetStringField(TEXT("topic"));
        UE_LOG(LogROS, Log, TEXT("[%s] Received message at Topic [%s]."),
			*FString(__FUNCTION__), *Topic);

        TSharedPtr< FJsonObject > MsgObject = JsonObject->GetObjectField(TEXT("msg"));

        // Find corresponding subscriber
        bool IsTopicFound = false;
        TSharedPtr<FROSBridgeSubscriber> Subscriber;
        for (int i = 0; i < ListSubscribers.Num(); i++)
        {
            if (ListSubscribers[i]->GetTopic() == Topic)
            {
#if UE_BUILD_DEBUG
                UE_LOG(LogROS, Log, TEXT("[%s] Subscriber Found. Id = %d. "), *FString(__FUNCTION__), i);
#endif
                Subscriber = ListSubscribers[i];
                IsTopicFound = true; break;
            }
        }

        if (!IsTopicFound)
        {
            UE_LOG(LogROS, Error, TEXT("[%s] Error: Topic [%s] subscriber not Found. "),
				*FString(__FUNCTION__), *Topic);
        }
        else
        {
            TSharedPtr<FROSBridgeMsg> ROSBridgeMsg;
            ROSBridgeMsg = Subscriber->ParseMessage(MsgObject);
            TSharedPtr<FProcessTask> RenderTask = MakeShareable<FProcessTask>(new FProcessTask(Subscriber, Topic, ROSBridgeMsg));

            QueueTask.Enqueue(RenderTask);
        }
    }
    else if (Op == TEXT("service_response"))
    {
        FString Id = JsonObject->GetStringField(TEXT("id"));
        FString ServiceName = JsonObject->GetStringField(TEXT("service"));
        TSharedPtr< FJsonObject > ValuesObj; 
        if (JsonObject->HasField("values")) // has values
            ValuesObj = JsonObject->GetObjectField(TEXT("values"));
        else
            ValuesObj = MakeShareable(new FJsonObject);

        bool bFoundService = false; 
        int FoundServiceIndex; 
        LockArrayService.Lock(); // lock mutex, when access ArrayService
        for (int i = 0; i < ArrayService.Num(); i++)
        {
            if (ArrayService[i]->Name == ServiceName &&
                ArrayService[i]->Id == Id)
            {
                ArrayService[i]->bIsResponsed = true; 
                check(ArrayService[i]->Response.IsValid());
                ArrayService[i]->Response->FromJson(ValuesObj);
                bFoundService = true; 
                FoundServiceIndex = i;
            }
        }
        LockArrayService.Unlock(); // unlock mutex

        if (!bFoundService)
        {
            UE_LOG(LogROS, Error, TEXT("[%s] Error: Service Name [%s] Id [%s] not found. "),
				*FString(__FUNCTION__), *ServiceName, *Id);
        } 
    }
    else if (Op == "call_service")
    {
        FString Id = JsonObject->GetStringField(TEXT("id")); 
        // there is always an Id for rosbridge_server generated service call
        FString ServiceName = JsonObject->GetStringField(TEXT("service"));
        TSharedPtr< FJsonObject > ArgsObj;
        if (JsonObject->HasField("args")) // has values
            ArgsObj = JsonObject->GetObjectField(TEXT("args"));
        else
            ArgsObj = MakeShareable(new FJsonObject);

        // call service in block mode
        bool bFoundService = false;
        int FoundServiceIndex = -1;
        for (int i = 0; i < ListServiceServers.Num(); i++)
            if (ListServiceServers[i]->GetName() == ServiceName)
            {
                bFoundService = true;
                FoundServiceIndex = i; 
                break; 
            }

        if (!bFoundService)
        {
            UE_LOG(LogROS, Error, TEXT("[%s] Error: Service Name [%s] Id [%s] not found. "),
				*FString(__FUNCTION__), *ServiceName, *Id);
        }
        else
        {
#if UE_BUILD_DEBUG
            UE_LOG(LogROS, Log, TEXT("[%s] Info: Service Name [%s] Id [%s] found, calling callback function."),
				*FString(__FUNCTION__), *ServiceName, *Id);
#endif
            TSharedPtr<FROSBridgeSrv::SrvRequest> Request = ListServiceServers[FoundServiceIndex]->FromJson(ArgsObj); 
            TSharedPtr<FROSBridgeSrv::SrvResponse > Response = ListServiceServers[FoundServiceIndex]->Callback(Request); // block 
            PublishServiceResponse(ServiceName, Id, Response); 
        }
    }
}

// Create runnable instance and run the thread;
void FROSBridgeHandler::Connect()
{
    Runnable = new FROSBridgeHandlerRunnable(this);
    Thread = FRunnableThread::Create(Runnable, TEXT("ROSBridgeHandlerRunnable"), 0, TPri_BelowNormal);
}

// Unsubscribe / Unadvertise all topics
// Stop the thread
void FROSBridgeHandler::Disconnect()
{
	// Un-register everything
	if (Client.IsValid() && IsClientConnected())
	{
		// Unsubscribe all topics
		for (int i = 0; i < ListSubscribers.Num(); i++)
		{
			UE_LOG(LogROS, Log, TEXT("[%s] Unsubscribing Topic %s"),
				*FString(__FUNCTION__), *ListSubscribers[i]->GetTopic());
			FString WebSocketMessage = FROSBridgeMsg::UnSubscribe(ListSubscribers[i]->GetTopic());
			Client->Send(WebSocketMessage);
		}

		// Unadvertise all topics
		for (int i = 0; i < ListPublishers.Num(); i++)
		{
			UE_LOG(LogROS, Log, TEXT("[%s] Unadvertising Topic %s"),
				*FString(__FUNCTION__), *ListPublishers[i]->GetTopic());
			FString WebSocketMessage = FROSBridgeMsg::UnAdvertise(ListPublishers[i]->GetTopic());
			Client->Send(WebSocketMessage);
		}

		// Unadvertise all service servers
		for (int i = 0; i < ListServiceServers.Num(); i++)
		{
			UE_LOG(LogROS, Log, TEXT("[%s] Unadvertising Service [%s]"),
				*FString(__FUNCTION__), *ListServiceServers[i]->GetName());
			FString WebSocketMessage = FROSBridgeSrv::UnadvertiseService(ListServiceServers[i]->GetName());
			Client->Send(WebSocketMessage);
		}

#if UE_BUILD_DEBUG
		if (ListPendingSubscribers.Num() > 0)
		{
			UE_LOG(LogROS, Log, TEXT("[%s] ROSBridgeHandler is shutting down, but there were still pending subscribers"),
				*FString(__FUNCTION__));
		}

		if (ListPendingPublishers.Num() > 0)
		{
			UE_LOG(LogROS, Log, TEXT("[%s] ROSBridgeHandler is shutting down, but there were still pending publishers"),
				*FString(__FUNCTION__));
		}

		if (ListPendingServiceServers.Num() > 0)
		{
			UE_LOG(LogROS, Log, TEXT("[%s] ROSBridgeHandler is shutting down, but there were still pending service servers"),
				*FString(__FUNCTION__));
		}
#endif

	}

    // Kill the thread and the Runnable
    if(Runnable) Runnable->Stop(); 
    if(Thread) Thread->WaitForCompletion();
	if(Runnable) Runnable->Exit();

	if(Client.IsValid()) Client->Destroy();

    delete Thread;
    delete Runnable;

    Thread = NULL;
    Client = NULL;
    Runnable = NULL;
}

DEPRECATED(4.18, "Render() is deprecated, use Process() instead.")
void FROSBridgeHandler::Render()
{
	Process();
}

// Update for each frame / substep
void FROSBridgeHandler::Process()
{
    while (!QueueTask.IsEmpty())
    {
        TSharedPtr<FProcessTask> RenderTask;
        QueueTask.Dequeue(RenderTask);

        TSharedPtr<FROSBridgeMsg> Msg = RenderTask->Message;
        UE_LOG(LogROS, Log, TEXT("[%s] Rendering task [%s]"),
			*FString(__FUNCTION__), *RenderTask->Topic);
        RenderTask->Subscriber->Callback(Msg);

        // delete Msg;
    }

    LockArrayService.Lock(); // lock mutex, when access ArrayService
    for (int i = 0; i < ArrayService.Num(); i++)
    {
        if (ArrayService[i]->bIsResponsed)
        {
            ArrayService[i]->Client->Callback(
                ArrayService[i]->Request,
                ArrayService[i]->Response
            ); 
            ArrayService[i]->bIsProcessed = true; 
        }
    }
    for (int i = 0; i < ArrayService.Num(); i++)
    {
        if (ArrayService[i]->bIsProcessed)
        {
            ArrayService.RemoveAt(i);
            i--;
        }
    }
    LockArrayService.Unlock(); // unlock mutex of ArrayService
}

void FROSBridgeHandler::PublishServiceResponse(FString InService, FString InId,
    TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse)
{
	if (!Client.IsValid()) return;
	if (!bIsClientConnected) return;

    FString MsgToSend = FROSBridgeSrv::ServiceResponse(InService, InId, InResponse);
    Client->Send(MsgToSend); 
}

void FROSBridgeHandler::PublishMsg(FString InTopic, TSharedPtr<FROSBridgeMsg> InMsg)
{
	if (!Client.IsValid()) return;
	if (!bIsClientConnected) return;

    FString MsgToSend = FROSBridgeMsg::Publish(InTopic, InMsg);
    Client->Send(MsgToSend);
}

void FROSBridgeHandler::CallService(TSharedPtr<FROSBridgeSrvClient> InSrvClient,
                                    TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest,
                                    TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse)
{
    FString Name = InSrvClient->GetName(); 
    FString Id = Name + TEXT("_request_") + FString::FromInt(FMath::RandRange(0, 10000000));
    LockArrayService.Lock(); // lock mutex, when access ArrayService

    TSharedPtr<FServiceTask> ServiceTask = MakeShareable<FServiceTask>(new FServiceTask(InSrvClient, Name, Id, InRequest, InResponse)); 
    ArrayService.Add(ServiceTask);

    LockArrayService.Unlock(); 
    CallServiceImpl(Name, InRequest, Id); 
}

void FROSBridgeHandler::CallServiceImpl(FString Name, TSharedPtr<FROSBridgeSrv::SrvRequest> Request, FString Id)
{
	if (!Client.IsValid()) return;
	if (!bIsClientConnected) return;

    FString MsgToSend = FROSBridgeSrv::CallService(Name, Request, Id);
    Client->Send(MsgToSend); 
}

