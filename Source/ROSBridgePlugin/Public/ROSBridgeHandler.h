#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"

#include "ROSBridgeMsg.h"
#include "ROSBridgePublisher.h"
#include "ROSBridgeSubscriber.h"
#include "UObject.h"

#include "WebSocket.h"

class FROSBridgeHandler {

private:
    /* Subclasses */
    /* FRenderTask: Representation of subscribed messages,
     *              can be processed by Render()*/
    struct FRenderTask {
        FRenderTask(FROSBridgeSubscriber* Subscriber_, FString Topic_,
                    FROSBridgeMsg* Message_):
            Subscriber(Subscriber_), Topic(Topic_), Message(Message_) {
        }
        FROSBridgeSubscriber* Subscriber;
        FString Topic;
        FROSBridgeMsg* Message;
    };

    class FROSBridgeHandlerRunnable : public FRunnable {
    public:
        FROSBridgeHandlerRunnable(FROSBridgeHandler* ROSBridgeHandler):
            Handler(ROSBridgeHandler),
            StopCounter(0)
        {
        }

        // Create connection, bind functions to WebSocket Client, and Connect.
        virtual bool Init() override;

        // Process subscribed messages using "Send"
        virtual uint32 Run() override;

        // set the stop counter and disconnect
        virtual void Stop() override;

    private:
        // Increase the StopCounter to stop the Runnable thread.
        FThreadSafeCounter StopCounter;
        FROSBridgeHandler* Handler;
    };

    FString Host;
    int32 Port;

    float ClientInterval;

    // TSharedPtr<FWebSocket> Client;
    FWebSocket* Client;
    FThreadSafeBool bIsClientConnected;

    TArray< FROSBridgeSubscriber* > ListSubscribers;
    TArray< FROSBridgePublisher* >  ListPublishers;
    TQueue< FRenderTask* > QueueTask;

    FROSBridgeHandlerRunnable* Runnable;
    FRunnableThread* Thread;

    // When message comes, create FRenderTask instances and push it
    // into QueueTask.
    void OnMessage(void* data, int32 length);
    void Run();

    // friendship declaration
    friend class FROSBridgeHandlerRunnable;

public:
    FROSBridgeHandler(FString Host_, int32 Port_):
        Host(Host_), Port(Port_),
        ClientInterval(0.01), bIsClientConnected(false)
    {

    }

    float GetClientInterval() const
    {
        return ClientInterval;
    }

    void SetClientInterval(float NewInterval)
    {
        ClientInterval = NewInterval;
    }

    bool IsClientConnected() const
    {
        return bIsClientConnected;
    }

    void SetClientConnected(bool val)
    {
        bIsClientConnected.AtomicSet(val);
    }

    FString GetHost() const
    {
        return Host;
    }

    int32 GetPort() const
    {
        return Port;
    }

    void AddSubscriber(FROSBridgeSubscriber* Subscriber)
    {
        ListSubscribers.Add(Subscriber);
    }

    void AddPublisher(FROSBridgePublisher* Publisher)
    {
        ListPublishers.Add(Publisher);
    }

    void AddServiceResponse(UObject ServiceResponse)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not Implemented Yet!"));
    }

    // Create runnable instance and run the thread;
    void Connect();

    // Unsubscribe / Unadvertise all messages
    // Stop the thread
    void Disconnect();

    // Update for each frame / substep
    void Render();
};
