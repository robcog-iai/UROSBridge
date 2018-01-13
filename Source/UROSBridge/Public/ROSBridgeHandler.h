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

class UROSBRIDGE_API FROSBridgeHandler 
{

private:
    /* Subclasses */
    /* FRenderTask: Representation of subscribed messages,
     *              can be processed by Render()*/
    struct FRenderTask 
	{
        FRenderTask(
			TSharedPtr<FROSBridgeSubscriber> InSubscriber,
			FString InTopic,
			TSharedPtr<FROSBridgeMsg> InMessage) :
            Subscriber(InSubscriber),
			Topic(InTopic),
			Message(InMessage)
		{
		}

        TSharedPtr<FROSBridgeSubscriber> Subscriber;
        FString Topic;
        TSharedPtr<FROSBridgeMsg> Message;
    };

    /* FServiceTask: Service call results, can be processed by Render() */
    struct FServiceTask 
	{
        FServiceTask(
			TSharedPtr<FROSBridgeSrvClient> InClient,
			FString InServiceName,
            FString InID) :
            Client(InClient),
			Name(InServiceName),
			ID(InID),
            bIsResponsed(false),
			bIsProcessed(false) 
		{
		}

        FServiceTask(
			TSharedPtr<FROSBridgeSrvClient> InClient,
			FString InServiceName,
            FString InID,
			TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest,
            TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse) :
            Client(InClient),
			Name(InServiceName),
			ID(InID),
            Request(InRequest),
			Response(InResponse),
            bIsResponsed(false),
			bIsProcessed(false) 
		{
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
        FROSBridgeHandlerRunnable(
			FROSBridgeHandler* ROSBridgeHandler) :
            StopCounter(0),
			Handler(ROSBridgeHandler)
        {
        }

        // Create connection, bind functions to WebSocket Client, and Connect.
        virtual bool Init() override;

        // Process subscribed messages using "Send"
        virtual uint32 Run() override;

        // Set the stop counter and disconnect
        virtual void Stop() override;

    private:
        // Increase the StopCounter to stop the Runnable thread.
        FThreadSafeCounter StopCounter;
        FROSBridgeHandler* Handler;
    };

    FString Host;
    int32 Port;
	bool bIsConnected;
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
    void OnMessage(void* Data, int32 Length);

    void CallServiceImpl(FString Name,
        TSharedPtr<FROSBridgeSrv::SrvRequest> Request, FString Id);

    // friendship declaration
    friend class FROSBridgeHandlerRunnable;

public:
    FROSBridgeHandler(FString InHost, int32 InPort):
        Host(InHost), Port(InPort),
        ClientInterval(0.01),
		bIsClientConnected(false),
		bIsConnected(false)
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

	bool IsConnected() const
	{
		return bIsConnected;
	}

	void SetConnected(bool bVal)
	{
		bIsConnected = bVal;
	}

    bool IsClientConnected() const
    {
        return bIsClientConnected;
    }

    void SetClientConnected(bool bVal)
    {
        bIsClientConnected.AtomicSet(bVal);
    }

    FString GetHost() const
    {
        return Host;
    }

    int32 GetPort() const
    {
        return Port;
    }

    void AddSubscriber(TSharedPtr<FROSBridgeSubscriber> InSubscriber)
    {
        ListSubscribers.Add(InSubscriber);
    }

    void AddPublisher(TSharedPtr<FROSBridgePublisher> InPublisher)
    {
        ListPublishers.Add(InPublisher);
    }

    void AddServiceServer(TSharedPtr<FROSBridgeSrvServer> InServer)
    {
        ListServiceServer.Add(InServer);
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

	DEPRECATED(4.18, "Render() is deprecated, use Process() instead.")
	void Render();

    // Update for each frame / substep
    void Process();
};
