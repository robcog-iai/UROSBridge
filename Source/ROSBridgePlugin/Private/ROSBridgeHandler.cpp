#include "IROSBridgePlugin.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Networking.h"
#include "Json.h"
#include "ROSBridgeHandler.h"


static void CallbackOnConnection(FROSBridgeHandler* Handler)
{
    UE_LOG(LogTemp, Warning, TEXT("Websocket Connected."));
    Handler->SetClientConnected(true);
}

static void CallbackOnError()
{
    UE_LOG(LogTemp, Warning, TEXT("Error in Websocket."));
}

// Create connection, bind functions to WebSocket Client, and Connect.
bool FROSBridgeHandler::FROSBridgeHandlerRunnable::Init()
{
    UE_LOG(LogTemp, Log, TEXT("FROSBridgeHandlerRunnable Thread Init()"));

    FIPv4Address IPAddress;
    FIPv4Address::Parse(Handler->GetHost(), IPAddress);

    FIPv4Endpoint Endpoint(IPAddress, Handler->GetPort());
    Handler->Client = new FWebSocket(Endpoint.ToInternetAddr().Get());

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
    while (StopCounter.GetValue() == 0){
        if (Handler->Client)
            Handler->Client->Tick();
        FPlatformProcess::Sleep(Handler->GetClientInterval());
    }
    UE_LOG(LogTemp, Log, TEXT("Run() function stopped. "));
    return 0;
}

// set the stop counter and disconnect
void FROSBridgeHandler::FROSBridgeHandlerRunnable::Stop()
{
    UE_LOG(LogTemp, Log, TEXT("Stop() function. "));
    StopCounter.Increment();
}


// Callback function when message comes from WebSocket
void FROSBridgeHandler::OnMessage(void* data, int32 length)
{
    char * CharMessage = new char [length + 1];
    memcpy(CharMessage, data, length);
    CharMessage[length] = 0;

    FString JsonMessage = UTF8_TO_TCHAR(CharMessage);

    // Parse Json Message Here
    TSharedRef< TJsonReader<> > Reader =
            TJsonReaderFactory<>::Create(JsonMessage);
    TSharedPtr< FJsonObject > JsonObject;
    bool DeserializeState = FJsonSerializer::Deserialize(Reader, JsonObject);
    if (!DeserializeState)
    {
        UE_LOG(LogTemp, Error, TEXT("Deserialization Error. "));
        return;
    }

    FString Topic = JsonObject->GetStringField(TEXT("topic"));
    TSharedPtr< FJsonObject > MsgObject = JsonObject->GetObjectField(TEXT("msg"));
    TSharedPtr< FROSBridgeMsg > ROSBridgeMsg;

    // Find corresponding subscriber
    bool IsTopicFound = false;
    TSharedPtr<FROSBridgeSubscriber> Subscriber;
    for (int i = 0; i < ListSubscribers.Num(); i++)
    {
        if (ListSubscribers[i]->GetMessageTopic() == Topic)
        {
            Subscriber = ListSubscribers[i];
            IsTopicFound = true; break;
        }
    }

    if (!IsTopicFound)
    {
        UE_LOG(LogTemp, Error, TEXT("Error: Topic %s not Found. "), *Topic);
    }
    else
    {
        ROSBridgeMsg = Subscriber->ParseMessage(MsgObject.Get());
        TSharedPtr<FRenderTask> RenderTask = MakeShareable(
             new FRenderTask(Subscriber.Get(), Topic, ROSBridgeMsg.Get())
        );

        QueueTask.Enqueue(RenderTask);
    }

    delete [] CharMessage;
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
    UE_LOG(LogTemp, Log, TEXT("Subscribe all topics. "));
    for (int i = 0; i < ListSubscribers.Num(); i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("Subscribing Topic %s"), *ListSubscribers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::Subscribe(ListSubscribers[i]->GetMessageTopic());
        Client->Send(WebSocketMessage);
    }

    // Advertise all topics
    UE_LOG(LogTemp, Log, TEXT("Advertise all topics. "));
    for (int i = 0; i < ListPublishers.Num(); i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("Unadvertising Topic %s"), *ListPublishers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::Advertise(ListPublishers[i]->GetMessageTopic(),
                                                            ListPublishers[i]->GetMessageType());
        Client->Send(WebSocketMessage);
    }

}

// Unsubscribe / Unadvertise all topics
// Stop the thread
void FROSBridgeHandler::Disconnect()
{
    // Unsubscribe all topics
    UE_LOG(LogTemp, Log, TEXT("Unsubscribe all topics. "));
    for (int i = 0; i < ListSubscribers.Num(); i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("Unsubscribing Topic %s"), *ListSubscribers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::UnSubscribe(ListSubscribers[i]->GetMessageTopic());
        Client->Send(WebSocketMessage);
    }

    // Unadvertise all topics
    UE_LOG(LogTemp, Log, TEXT("Unadvertise all topics. "));
    for (int i = 0; i < ListPublishers.Num(); i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("Unadvertising Topic %s"), *ListPublishers[i]->GetMessageTopic());
        FString WebSocketMessage = FROSBridgeMsg::UnAdvertise(ListPublishers[i]->GetMessageTopic());
        Client->Send(WebSocketMessage);
    }

    // Kill the thread and the Runnable
    UE_LOG(LogTemp, Log, TEXT("Kill the thread. "));
    Thread->Kill();
    Thread->WaitForCompletion();

    UE_LOG(LogTemp, Log, TEXT("Delete the thread. "));
    delete Thread;
    UE_LOG(LogTemp, Log, TEXT("Set Thread to NULL. "));
    Thread = NULL;

    UE_LOG(LogTemp, Log, TEXT("Delete the Client. "));
    delete Client;
    Client = NULL;

    UE_LOG(LogTemp, Log, TEXT("Delete the Runnable. "));
    delete Runnable;
    Runnable = NULL;
}

// Run
void FROSBridgeHandler::Run()
{
    // Do not use this function.
    check(false);
}

// Update for each frame / substep
void FROSBridgeHandler::Render()
{
    while (!QueueTask.IsEmpty())
    {
        TSharedPtr<FRenderTask> RenderTask;
        QueueTask.Dequeue(RenderTask);

        FROSBridgeMsg* Msg = RenderTask->Message;
        RenderTask->Subscriber->CallBack(Msg);
    }
}
