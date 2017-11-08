// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#include "ROSBridgeHandler.h"
#include "UROSBridge.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Networking.h"
#include "Json.h"

static void CallbackOnConnection(FROSBridgeHandler* Handler)
{
    UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler] Websocket server connected."));
    Handler->SetClientConnected(true);
}

static void CallbackOnError()
{
    UE_LOG(LogROS, Error, TEXT("[FROSBridgeHandler] Error in Websocket."));
}

// Create connection, bind functions to WebSocket Client, and Connect.
bool FROSBridgeHandler::FROSBridgeHandlerRunnable::Init()
{
#if UE_BUILD_DEBUG
    UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandlerRunnable::Init]"));
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
    ConnectedCallback.BindStatic(&CallbackOnConnection, this->Handler);
    Handler->Client->SetConnectedCallBack(ConnectedCallback);

    // Bind Error callback
    FWebsocketInfoCallBack ErrorCallback;
    ErrorCallback.BindStatic(&CallbackOnError);
    Handler->Client->SetErrorCallBack(ErrorCallback);

    Handler->Client->Connect();
    return true;
}

// Process subscribed messages
uint32 FROSBridgeHandler::FROSBridgeHandlerRunnable::Run()
{
    while (StopCounter.GetValue() == 0)
	{
        if (Handler->Client.IsValid() && !Handler->Client->IsDestroyed)
            Handler->Client->Tick();
        FPlatformProcess::Sleep(Handler->GetClientInterval());
    }
    return 0;
}

// set the stop counter and disconnect
void FROSBridgeHandler::FROSBridgeHandlerRunnable::Stop()
{
    StopCounter.Increment();
}


// Callback function when message comes from WebSocket
void FROSBridgeHandler::OnMessage(void* data, int32 length)
{
    char * CharMessage = new char [length + 1];
    memcpy(CharMessage, data, length);
    CharMessage[length] = 0;
    FString JsonMessage = UTF8_TO_TCHAR(CharMessage);
    delete[] CharMessage;

#if UE_BUILD_DEBUG
    UE_LOG(LogROS, Error, TEXT("[FROSBridgeHandler::OnMessage] Json Message: %s"), *JsonMessage);
#endif

    // Parse Json Message Here
    TSharedRef< TJsonReader<> > Reader =
            TJsonReaderFactory<>::Create(JsonMessage);
    TSharedPtr< FJsonObject > JsonObject;
    bool DeserializeState = FJsonSerializer::Deserialize(Reader, JsonObject);
    if (!DeserializeState)
    {
        UE_LOG(LogROS, Error, TEXT("[FROSBridgeHandler::OnMessage] Deserialization Error. Message Contents: %s"), *JsonMessage);
        return;
    }

    FString Op = JsonObject->GetStringField(TEXT("op"));

    if (Op == TEXT("publish")) // Message 
    {
        FString Topic = JsonObject->GetStringField(TEXT("topic"));
        UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::OnMessage] Received message at Topic [%s]. "), *Topic);

        TSharedPtr< FJsonObject > MsgObject = JsonObject->GetObjectField(TEXT("msg"));

        // Find corresponding subscriber
        bool IsTopicFound = false;
        TSharedPtr<FROSBridgeSubscriber> Subscriber;
        for (int i = 0; i < ListSubscribers.Num(); i++)
        {
            if (ListSubscribers[i]->GetMessageTopic() == Topic)
            {
#if UE_BUILD_DEBUG
                UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::OnMessage] Subscriber Found. Id = %d. "), i);
#endif
                Subscriber = ListSubscribers[i];
                IsTopicFound = true; break;
            }
        }

        if (!IsTopicFound)
        {
            UE_LOG(LogROS, Error, TEXT("[FROSBridgeHandler::OnMessage] Error: Topic [%s] subscriber not Found. "), *Topic);
        }
        else
        {
            TSharedPtr<FROSBridgeMsg> ROSBridgeMsg;
            ROSBridgeMsg = Subscriber->ParseMessage(MsgObject);
            TSharedPtr<FRenderTask> RenderTask = MakeShareable<FRenderTask>(new FRenderTask(Subscriber, Topic, ROSBridgeMsg));

            QueueTask.Enqueue(RenderTask);
        }
    }
    else if (Op == TEXT("service_response"))
    {
        FString ID = JsonObject->GetStringField(TEXT("id"));
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
                ArrayService[i]->ID == ID)
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
            UE_LOG(LogROS, Error, TEXT("[FROSBridgeHandler::OnMessage] Error: Service Name [%s] Id [%s] not found. "), *ServiceName, *ID);
        } 
    }
    else if (Op == "call_service")
    {
        FString ID = JsonObject->GetStringField(TEXT("id")); 
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
        for (int i = 0; i < ListServiceServer.Num(); i++)
            if (ListServiceServer[i]->GetName() == ServiceName)
            {
                bFoundService = true;
                FoundServiceIndex = i; 
                break; 
            }

        if (!bFoundService)
        {
            UE_LOG(LogROS, Error, TEXT("[FROSBridgeHandler::OnMessage] Error: Service Name [%s] Id [%s] not found. "), *ServiceName, *ID);
        }
        else
        {
#if UE_BUILD_DEBUG
            UE_LOG(LogROS, Log, TEXT("Info: Service Name [%s] Id [%s] found, calling callback function."), *ServiceName, *ID);
#endif
            TSharedPtr<FROSBridgeSrv::SrvRequest> Request = ListServiceServer[FoundServiceIndex]->FromJson(ArgsObj); 
            TSharedPtr<FROSBridgeSrv::SrvResponse > Response = ListServiceServer[FoundServiceIndex]->CallBack(Request); // block 
            PublishServiceResponse(ServiceName, ID, Response); 
        }
    }
}

// Create runnable instance and run the thread;
void FROSBridgeHandler::Connect()
{
    Runnable = //  MakeShareable(
        new FROSBridgeHandlerRunnable(this);
    // );
    Thread = FRunnableThread::Create(Runnable, TEXT("ROSBridgeHandlerRunnable"),
                                     0, TPri_BelowNormal);
    while (!IsClientConnected())
        FPlatformProcess::Sleep(0.01);

    // Subscribe all topics
    UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Connect] Subscribe all topics. "));
    for (int i = 0; i < ListSubscribers.Num(); i++)
    {
        UE_LOG(LogROS, Warning, TEXT("[FROSBridgeHandler::Connect] Subscribing Topic %s"), *ListSubscribers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::Subscribe(ListSubscribers[i]->GetMessageTopic(),
                                                            ListSubscribers[i]->GetMessageType());
        Client->Send(WebSocketMessage);
    }

    // Advertise all topics
    UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Connect] Advertise all topics. "));
    for (int i = 0; i < ListPublishers.Num(); i++)
    {
        UE_LOG(LogROS, Warning, TEXT("[FROSBridgeHandler::Connect] Advertising Topic %s"), *ListPublishers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::Advertise(ListPublishers[i]->GetMessageTopic(),
                                                            ListPublishers[i]->GetMessageType());
        Client->Send(WebSocketMessage);
    }

    // Advertise all service servers
    for (int i = 0; i < ListServiceServer.Num(); i++)
    {
        UE_LOG(LogROS, Warning, TEXT("[FROSBridgeHandler::Connect] Advertising Service [%s] of type [%s]"), *ListServiceServer[i]->GetName(), *ListServiceServer[i]->GetType());
        FString WebSocketMessage = FROSBridgeSrv::AdvertiseService(ListServiceServer[i]->GetName(), 
                                                                   ListServiceServer[i]->GetType());
        Client->Send(WebSocketMessage); 
    }
}

// Unsubscribe / Unadvertise all topics
// Stop the thread
void FROSBridgeHandler::Disconnect()
{
    // Unsubscribe all topics
    UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Disconnect] Unsubscribe all topics. "));
    for (int i = 0; i < ListSubscribers.Num(); i++)
    {
        UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Disconnect] Unsubscribing Topic %s"), *ListSubscribers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::UnSubscribe(ListSubscribers[i]->GetMessageTopic());
        Client->Send(WebSocketMessage);
    }

    // Unadvertise all topics
    UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Disconnect] Unadvertise all topics. "));
    for (int i = 0; i < ListPublishers.Num(); i++)
    {
        UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Disconnect] Unadvertising Topic %s"), *ListPublishers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::UnAdvertise(ListPublishers[i]->GetMessageTopic());
        Client->Send(WebSocketMessage);
    }

    // Unadvertise all service servers
    UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Disconnect] Unadvertise all services. "));
    for (int i = 0; i < ListServiceServer.Num(); i++)
    {
        UE_LOG(LogROS, Log, TEXT("[FROSBridgeHandler::Disconnect] Unadvertising Service [%s]"), *ListServiceServer[i]->GetName());
        FString WebSocketMessage = FROSBridgeSrv::UnadvertiseService(ListServiceServer[i]->GetName());
        Client->Send(WebSocketMessage);
    }

    // Kill the thread and the Runnable
    Runnable->Stop(); 
    Thread->WaitForCompletion();

	Client->Destroy();

    delete Thread;
    delete Runnable;

    Thread = NULL;
    Client = NULL;
    Runnable = NULL;
}

// Update for each frame / substep
void FROSBridgeHandler::Render()
{
    while (!QueueTask.IsEmpty())
    {
        TSharedPtr<FRenderTask> RenderTask;
        QueueTask.Dequeue(RenderTask);

        TSharedPtr<FROSBridgeMsg> Msg = RenderTask->Message;
        RenderTask->Subscriber->CallBack(Msg);

        // delete Msg;
    }

    LockArrayService.Lock(); // lock mutex, when access ArrayService
    for (int i = 0; i < ArrayService.Num(); i++)
    {
        if (ArrayService[i]->bIsResponsed)
        {
            ArrayService[i]->Client->CallBack(
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

void FROSBridgeHandler::PublishServiceResponse(FString Service, FString ID,
    TSharedPtr<FROSBridgeSrv::SrvResponse> Response)
{
    FString MsgToSend = FROSBridgeSrv::ServiceResponse(Service, ID, Response); 
    Client->Send(MsgToSend); 
}

void FROSBridgeHandler::PublishMsg(FString Topic, TSharedPtr<FROSBridgeMsg> Msg)
{
    FString MsgToSend = FROSBridgeMsg::Publish(Topic, Msg);
    Client->Send(MsgToSend);
}

void FROSBridgeHandler::CallService(TSharedPtr<FROSBridgeSrvClient> SrvClient,
                                    TSharedPtr<FROSBridgeSrv::SrvRequest> Request,
                                    TSharedPtr<FROSBridgeSrv::SrvResponse> Response)
{
    FString Name = SrvClient->GetName(); 
    FString ID = Name + TEXT("_request_") + FString::FromInt(FMath::RandRange(0, 10000000));
    LockArrayService.Lock(); // lock mutex, when access ArrayService

    TSharedPtr<FServiceTask> ServiceTask = MakeShareable<FServiceTask>(new FServiceTask(SrvClient, Name, ID, Request, Response)); 
    ArrayService.Add(ServiceTask);

    LockArrayService.Unlock(); 
    CallServiceImpl(Name, Request, ID); 
}

void FROSBridgeHandler::CallServiceImpl(FString Name, TSharedPtr<FROSBridgeSrv::SrvRequest> Request, FString ID)
{
    FString MsgToSend = FROSBridgeSrv::CallService(Name, Request, ID);
    Client->Send(MsgToSend); 
}

