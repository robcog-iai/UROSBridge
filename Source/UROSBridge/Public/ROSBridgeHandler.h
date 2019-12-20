// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "CoreGlobals.h"
#include "Containers/Queue.h"

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

	/**
	* FProcessTask: Representation of subscribed messages,
	*			  can be processed by Process()
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
	* Thread to handle ROS communication
	*/
	class FROSBridgeHandlerRunnable : public FRunnable
	{
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

		// Exits the runnable object. Called in the context of the aggregating thread to perform any cleanup.
		virtual void Exit() override;

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

	// Pending Subscribers/Publishes/Server Services have not yet been sent to ROSBridge
	TArray< TSharedPtr<FROSBridgeSubscriber> > ListPendingSubscribers;
	TArray< TSharedPtr<FROSBridgePublisher> >  ListPendingPublishers;
	TArray< TSharedPtr<FROSBridgeSrvServer> > ListPendingServiceServers;

	TArray< TSharedPtr<FROSBridgeSubscriber> > ListSubscribers;
	TArray< TSharedPtr<FROSBridgePublisher> >  ListPublishers;
	TArray< TSharedPtr<FROSBridgeSrvServer> > ListServiceServers;

	TQueue< TSharedPtr<FProcessTask> > QueueTask;
	TArray< TSharedPtr<FServiceTask> > ArrayService;

	FROSBridgeHandlerRunnable* Runnable;
	FRunnableThread* Thread;

	FCriticalSection LockTask;
	FCriticalSection LockArrayService;

	/** Index used to disambiguate thread instances for stats reasons */
	static int32 ThreadInstanceIdx;

	/** Callback delgate that will be triggerd when Error accurs
		User of the RosBridgeHandler can add their own callbacks by passing a 'FWebsocketInfoCallBack' to the Constructor */
	FWebsocketInfoCallBack ErrorCallbacks;

	/** Callback delgate that will be triggerd when connection is established
	User of the RosBridgeHandler can add their own callbacks by passing a 'FWebsocketInfoCallBack' to the Constructor */
	FWebsocketInfoCallBack ConnectedCallbacks;

	// Called when the WebSocket connection succeeds
	void OnConnection();

	// When message comes, create FProcessTask instances and push it into QueueTask.
	void OnMessage(void* Data, int32 Length);

	void CallServiceImpl(const FString& Name, TSharedPtr<FROSBridgeSrv::SrvRequest> Request, const FString& Id);

	// Friendship declaration
	friend class FROSBridgeHandlerRunnable;

public:
	FROSBridgeHandler(const FString& InHost, int32 InPort):
		Host(InHost), Port(InPort),
		ClientInterval(0.01),
		bIsClientConnected(false)
	{
	}

	//This creates a Handler with a custom ErrorCallback
	FROSBridgeHandler(const FString& InHost, int32 InPort, FWebsocketInfoCallBack UserErrorCallbacks, FWebsocketInfoCallBack UserConnectedCallbacks) :
		Host(InHost), Port(InPort),
		ClientInterval(0.01),
		bIsClientConnected(false),
		ErrorCallbacks(UserErrorCallbacks),
		ConnectedCallbacks(UserConnectedCallbacks)
	{
	}
  
	~FROSBridgeHandler()
	{
		ThreadCleanup();
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
		ListPendingSubscribers.Add(InSubscriber);
	}

	void AddPublisher(TSharedPtr<FROSBridgePublisher> InPublisher)
	{
		ListPendingPublishers.Add(InPublisher);
	}

	void AddServiceServer(TSharedPtr<FROSBridgeSrvServer> InServer)
	{
		ListPendingServiceServers.Add(InServer);
	}

	// Publish service response, used in service server
	void PublishServiceResponse(const FString& Service, const FString& Id,
		TSharedPtr<FROSBridgeSrv::SrvResponse> Response);

	// Publish ROS message to topics
	void PublishMsg(const FString& Topic, TSharedPtr<FROSBridgeMsg> Msg);

	// Call external ROS service
	void CallService(TSharedPtr<FROSBridgeSrvClient> SrvClient,
		TSharedPtr<FROSBridgeSrv::SrvRequest> Request,
		TSharedPtr<FROSBridgeSrv::SrvResponse> Response);

	// Create runnable instance and run the thread;
	void Connect();

	// Unsubscribe / Unadvertise all messages, stop the thread
	void Disconnect();

	// Stop runnable / thread / client
	void ThreadCleanup();

	// Update for each frame / substep
	void Process();
};
