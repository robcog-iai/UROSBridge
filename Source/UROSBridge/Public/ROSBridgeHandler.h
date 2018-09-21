// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

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

#include "ROSWebSocket.h"

/* Begin Subclasses */
/**
* FProcessTask: Representation of subscribed messages can be processed by Process()
*/
struct FProcessTask
{
	FProcessTask(
		TSharedPtr<FROSBridgeSubscriber> InSubscriber,
		const FString& InTopic,
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

/**
* FServiceTask: Service call results, can be processed by Process()
*/
struct FServiceTask
{
	FServiceTask(
		TSharedPtr<FROSBridgeSrvClient> InClient,
		const FString& InServiceName,
		const FString& InId) :
		Client(InClient),
		Name(InServiceName),
		Id(InId),
		bIsResponsed(false),
		bIsProcessed(false)
	{
	}

	FServiceTask(
		TSharedPtr<FROSBridgeSrvClient> InClient,
		const FString& InServiceName,
		const FString& InId,
		TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest,
		TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse) :
		Client(InClient),
		Name(InServiceName),
		Id(InId),
		Request(InRequest),
		Response(InResponse),
		bIsResponsed(false),
		bIsProcessed(false)
	{
	}

	TSharedPtr<FROSBridgeSrvClient> Client;
	FString Name;
	FString Id;
	TSharedPtr<FROSBridgeSrv::SrvRequest> Request;
	TSharedPtr<FROSBridgeSrv::SrvResponse> Response;
	bool bIsResponsed;
	bool bIsProcessed;
};

/**
* Thread to handle ROS communication (msg callbacks are not triggered here)
*/
class FROSBridgeHandlerRunnable : public FRunnable
{
public:
	// Constructor
	FROSBridgeHandlerRunnable(FROSBridgeHandler* InHandler) :
		StopCounter(0), Handler(InHandler)
	{
	}

	// Create connection, bind functions to WebSocket Client, and Connect.
	virtual bool Init() override;

	// Process subscribed messages using
	virtual uint32 Run() override;

	// Set the stop counter and disconnect
	virtual void Stop() override;

	// Exits the runnable object. Called in the context of the aggregating thread to perform any cleanup.
	virtual void Exit() override;

private:
	// Increase the StopCounter to stop the Runnable thread.
	FThreadSafeCounter StopCounter;
	FROSBridgeHandler* Handler;
};
/* End Subclasses */

class UROSBRIDGE_API FROSBridgeHandler
{
	// Give class access to private data
	friend class FROSBridgeHandlerRunnable;

public:
	// Constructor
	FROSBridgeHandler(const FString& InHost, int32 InPort);

	// Constructor with custom error and connection callback
	FROSBridgeHandler(const FString& InHost, int32 InPort,
		FROSWebsocketInfoSignature InErrorCallback,
		FROSWebsocketInfoSignature InConnectedCallback);

	// Destructor, clean thread
	~FROSBridgeHandler();

	// Create runnable instance and run the thread, try to connect
	void Connect();

	// Unsubscribe / un-advertise all messages, stop the thread
	void Disconnect();

	// Add a new subscriber
	void AddSubscriber(TSharedPtr<FROSBridgeSubscriber> InSubscriber);

	// Add a new publisher
	void AddPublisher(TSharedPtr<FROSBridgePublisher> InPublisher);

	// Add a new service server
	void AddServiceServer(TSharedPtr<FROSBridgeSrvServer> InServer);

	// Publish service response, used in service server
	void PublishServiceResponse(const FString& Service, const FString& Id,
		TSharedPtr<FROSBridgeSrv::SrvResponse> Response);

	// Publish ROS message to topics
	void PublishMsg(const FString& Topic, TSharedPtr<FROSBridgeMsg> Msg);

	// Call external ROS service
	void CallService(TSharedPtr<FROSBridgeSrvClient> SrvClient,
		TSharedPtr<FROSBridgeSrv::SrvRequest> Request,
		TSharedPtr<FROSBridgeSrv::SrvResponse> Response);

	// Trigger the callbacks on the received messages
	void Process();

	// Getters
	bool IsConnected() const { return bIsConnected; }
	FString GetHost() const { return Host; }
	int32 GetPort() const { return Port; }

private:
	// Callback when the connection succeeds
	void OnConnection();

	// Callback on connection error
	void OnError();

	// When a new message arrives, create a FProcessTask and push it to the QueueTask
	void OnMessage(void* Data, int32 Length);

	// Call service to send msg
	void CallServiceImpl(const FString& Name, TSharedPtr<FROSBridgeSrv::SrvRequest> Request, const FString& Id);

	// Stop runnable / thread / client
	void ThreadCleanup();

	// ROS server ip as string
	FString Host;

	// ROS server port
	int32 Port;

	// Communication thread sleep duration
	float ThreadSleep;

	// Websocket client
	TSharedPtr<FROSWebSocket> WSClient;

	// Flag marking the connection
	FThreadSafeBool bIsConnected;

	// Pending Subscribers/Publishes/Server Services have not yet been sent to ROSBridge
	TArray< TSharedPtr<FROSBridgeSubscriber> > ListPendingSubscribers;
	TArray< TSharedPtr<FROSBridgePublisher> >  ListPendingPublishers;
	TArray< TSharedPtr<FROSBridgeSrvServer> > ListPendingServiceServers;

	// Subscribers/publishers/server services
	TArray< TSharedPtr<FROSBridgeSubscriber> > ListSubscribers;
	TArray< TSharedPtr<FROSBridgePublisher> >  ListPublishers;
	TArray< TSharedPtr<FROSBridgeSrvServer> > ListServiceServers;

	// Messages/services to be processed
	TQueue< TSharedPtr<FProcessTask> > QueueTask;
	TArray< TSharedPtr<FServiceTask> > ArrayService;

	// Thread for the communication
	FROSBridgeHandlerRunnable* Runnable;
	FRunnableThread* Thread;

	FCriticalSection LockTask;
	FCriticalSection LockArrayService;

	/** Index used to disambiguate thread instances for stats reasons */
	static int32 ThreadInstanceIdx;

	/** Callback delegate that will be triggered when an error occurs
		User of the RosBridgeHandler can add their own callbacks by passing a 'FWebsocketInfoCallBack' to the Constructor */
	FROSWebsocketInfoSignature ErrorCallback;

	/** Callback delegate that will be triggered when connection is established
	User of the RosBridgeHandler can add their own callbacks by passing a 'FWebsocketInfoCallBack' to the Constructor */
	FROSWebsocketInfoSignature ConnectedCallback;
};
