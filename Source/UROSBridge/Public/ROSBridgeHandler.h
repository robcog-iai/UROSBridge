// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "ThreadingBase.h"
#include "Queue.h"

#include "ROSBridgeMsg.h"
#include "ROSBridgeSrv.h"
#include "ROSBridgePublisher.h"
#include "ROSBridgeSubscriber.h"
#include "ROSBridgeSrvClient.h"
#include "ROSBridgeSrvServer.h"

#include "WebSocket.h"

class UROSBRIDGE_API FROSBridgeHandler {

private:
    /* Subclasses */
    /* FRenderTask: Representation of subscribed messages,
     *              can be processed by Render()*/
    struct FRenderTask {
        FRenderTask(TSharedPtr<FROSBridgeSubscriber> Subscriber_, FString Topic_,
                    TSharedPtr<FROSBridgeMsg> Message_):
            Subscriber(Subscriber_), Topic(Topic_), Message(Message_) {
        }
        TSharedPtr<FROSBridgeSubscriber> Subscriber;
        FString Topic;
        TSharedPtr<FROSBridgeMsg> Message;
    };

    /* FServiceTask: Service call results, can be processed by Render() */
    struct FServiceTask {
        FServiceTask(TSharedPtr<FROSBridgeSrvClient> Client_, FString ServiceName_, 
            FString ID_) :
            Client(Client_), Name(ServiceName_), ID(ID_), 
            bIsResponsed(false), bIsProcessed(false) {
        }

        FServiceTask(TSharedPtr<FROSBridgeSrvClient> Client_, FString ServiceName_,
            FString ID_, TSharedPtr<FROSBridgeSrv::SrvRequest> Request_, 
            TSharedPtr<FROSBridgeSrv::SrvResponse> Response_) :
            Client(Client_), Name(ServiceName_), ID(ID_), 
            Request(Request_), Response(Response_),
            bIsResponsed(false), bIsProcessed(false) {
        }

        TSharedPtr<FROSBridgeSrvClient> Client;
        FString Name;
        FString ID; 
        TSharedPtr<FROSBridgeSrv::SrvRequest> Request; 
        TSharedPtr<FROSBridgeSrv::SrvResponse> Response;
        bool bIsResponsed; 
        bool bIsProcessed; 
    };

    class FROSBridgeHandlerRunnable : public FRunnable {
    public:
        FROSBridgeHandlerRunnable(FROSBridgeHandler* ROSBridgeHandler):
            StopCounter(0), Handler(ROSBridgeHandler)
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
    TSharedPtr<FWebSocket> Client;
    FThreadSafeBool bIsClientConnected;

    TArray< TSharedPtr<FROSBridgeSubscriber> > ListSubscribers;
    TArray< TSharedPtr<FROSBridgePublisher> >  ListPublishers;
    TArray< TSharedPtr<FROSBridgeSrvServer> > ListServiceServer;
    TQueue< TSharedPtr<FRenderTask> > QueueTask;
    TArray< TSharedPtr<FServiceTask> > ArrayService;

    FROSBridgeHandlerRunnable* Runnable;
    FRunnableThread* Thread;

    FCriticalSection LockTask; 
    FCriticalSection LockArrayService;

    // When message comes, create FRenderTask instances and push it
    // into QueueTask.
    void OnMessage(void* data, int32 length);

    void CallServiceImpl(FString Name,
        TSharedPtr<FROSBridgeSrv::SrvRequest> Request, FString ID);

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

    void AddSubscriber(TSharedPtr<FROSBridgeSubscriber> Subscriber)
    {
        ListSubscribers.Add(Subscriber);
    }

    void AddPublisher(TSharedPtr<FROSBridgePublisher> Publisher)
    {
        ListPublishers.Add(Publisher);
    }

    void AddServiceServer(TSharedPtr<FROSBridgeSrvServer> Server)
    {
        ListServiceServer.Add(Server); 
    }

    // Publish service response, used in service server
    void PublishServiceResponse(FString Service, FString ID,
        TSharedPtr<FROSBridgeSrv::SrvResponse> Response); 

    // Publish ROS message to topics
    void PublishMsg(FString Topic, TSharedPtr<FROSBridgeMsg> Msg);

    // Call external ROS service
    void CallService(TSharedPtr<FROSBridgeSrvClient> SrvClient,
        TSharedPtr<FROSBridgeSrv::SrvRequest> Request,
        TSharedPtr<FROSBridgeSrv::SrvResponse> Response);

    // Create runnable instance and run the thread;
    void Connect();

    // Unsubscribe / Unadvertise all messages
    // Stop the thread
    void Disconnect();

    // Update for each frame / substep
    void Render();
};
