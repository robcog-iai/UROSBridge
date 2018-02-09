### UROSBridge

#### Connection and disconnection

UROSBridge could be used in Unreal Actors or in timers. To use it in actors, we need to add a smart pointer to ROSBridgeHandler first:

```cpp

// NB: Your #include "AROSActor.generated.h" must be the last include in the actor header
#include "ROSBRidgeHandler.h"

/// ...

UCLASS()
class PROJECT_API AROSActor : public AActor
{
    GENERATED_BODY()

public:
    TSharedPtr<FROSBridgeHandler> Handler;
    ...
}
```

In Actor's `BeginPlay()` function, create handler instance and connect to the websocket server:

```cpp
void AROSActor::BeginPlay()
{
    Super::BeginPlay();

    // Set websocket server address to ws://127.0.0.1:9001
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(TEXT("127.0.0.1"), 9001));

    // Connect to ROSBridge Websocket server.
    Handler->Connect();

    // Add topic subscribers and publishers
    // Add service clients and servers
}
```

In Actor's `Tick(float)` function, add `Handler->Process()` function to let handler process incoming messages in the message queue.

```cpp
void AROSActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Do something

    Handler->Process();
}
```

In Actor's `Logout` or `EndPlay` function, add `Handler->Disconnect()` function before the parent class ends.

```cpp
void AROSActor::EndPlay(const EEndPlayReason::Type Reason)
{
    Handler->Disconnect();
    // Disconnect the handler before parent ends

    Super::EndPlay(Reason);
}
```

#### Publish Message

To publish message to a topic, we need to first advertise the topic in ROS bridge. In AROSActor's class definition, Add a ROSBridgePublisher smart pointer.

```cpp
UCLASS()
class PROJECT_API AROSActor : public AActor
{
    GENERATED_BODY()

public:
    TSharedPtr<FROSBridgeHandler> Handler;
    TSharedPtr<FROSBridgePublisher> Publisher; // This
    ...
}
```

In AROSActor's `BeginPlay()` function, create the publisher using its **type** and **topic**, and then register it to the ROSBridgeHandler.

```cpp
void AROSActor::BeginPlay()
{
    Super::BeginPlay();

    // Set websocket server address to ws://127.0.0.1:9001
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(TEXT("127.0.0.1"), 9001));

    // Connect to ROSBridge Websocket server.
    Handler->Connect();

    // **** Create publishers here ****
    Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TEXT("/talker"), TEXT("sensor_msgs/JointState")));
    Handler->AddPublisher(Publisher);
}
```

#### Subscribe to Topics

This plugin uses `FROSBridgeSubscriber` class interface to subscribe to topics. We need to extend a `FROSBridgeSubscriber` subclass for each topic we would like to subscribe to, implementing the constructor, destructor, `ParseMessage` function and `Callback` function.

##### Include Messages

In class header, the UROSBridge Message class header should be included. Then, define a 'Subscriber' subclass you will use to receive the topic messages.

```cpp
#include "ROSBridgeSubscriber.h"
#include "std_msgs/String.h"
#include "Core.h"

class FROSStringSubScriber : public FROSBridgeSubscriber
{
   FROSStringSubScriber(const FString& InTopic);
   ~FROSStringSubScriber() override;
   TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;
   void Callback(TSharedPtr<FROSBridgeMsg> InMsg) override;
}
```

##### Constructor

In class constructor, we need to call the parent class constructor to set type and topic for this subscriber.

```cpp
FROSStringSubScriber::FROSStringSubScriber(const FString& InTopic):
    FROSBridgeSubscriber(InTopic, TEXT("std_msgs/String"))
    {      
    }
```

##### Destructor

Class destructors will be required if you need to do some cleaning work after the ROS bridge client disconnects.

```
FROSStringSubScriber::~FROSStringSubScriber()
{
};
```

##### ParseMessage

`ParseMessage` function is used by ROSBridgeHandler to convert a `JSONObject` to `FROSBridgeMsg` instance. Create a ROSBridgeMessage class with specified message type (e.g. `std_msgs::String`) and call its `FromJson` method to parse the JSON message. Finally convert the pointer to a `FROSBridgeMsg` pointer.

```cpp
TSharedPtr<FROSBridgeMsg> FROSStringSubScriber::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
    TSharedPtr<std_msgs::String> StringMessage =
        MakeShareable<std_msgs::String>(new std_msgs::String());        
    StringMessage->FromJson(JsonObject);
    return StaticCastSharedPtr<FROSBridgeMsg>(StringMessage);
}
```

##### Callback

`Callback` is the callback function called when a new message comes and is successfully parsed to a `ROSBridgeMsg` instance. In this function, we need to first down-cast the `FROSBridgeMsg` pointer to a pointer of its subclass.

```cpp
void Callback(TSharedPtr<FROSBridgeMsg> InMsg)
{
    TSharedPtr<std_msgs::String> StringMessage = StaticCastSharedPtr<std_msgs::String>(InMsg);
    // downcast to subclass using StaticCastSharedPtr function

    UE_LOG(LogTemp, Log, TEXT("Message received! Content: %s"), *StringMessage->GetData());
    // do something with the message

    return;
}
```

##### In Unreal Actor

In Unreal Actors we need to add pointer to subscriber to the subscriber list

```cpp
void AROSActor::BeginPlay()
{
    Super::BeginPlay();

    // Set websocket server address to ws://127.0.0.1:9001
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(TEXT("127.0.0.1"), 9001));

    // Connect to ROSBridge Websocket server.
    Handler->Connect();

    // Add topic subscribers and publishers
    TSharedPtr<FROSStringSubScriber> Subscriber =
        MakeShareable<FROSStringSubScriber>(new FROSStringSubScriber(TEXT("/chatter")));
    Handler->AddSubscriber(Subscriber);
}
```

#### A note on ROSBridgeHandler

Connections to ROSBridge work via a [`ROSBridgeHandler`](../Source/UROSBridge/Public/ROSBridgeHandler.h) object.
There should only be one of these in your project.
If you have multiple actors that need to connect to ROS, a good pattern is to create a custom [GameInstance](https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Engine/UGameInstance/index.html), and store the `ROSBridgeHandler` object there as a public member.
Your actors can then access the `ROSBridgeHandler` by calling e.g. `this->GetGameInstance().Handler`

When the ROS Bridge Handler disconnects to server, it automatically destroys all subscriber instances.

#### Request Service

A service consists of two parts: Request and Response. Clients send out requests, and then get response from server. Servers process received requests and send out response.

To send service requests in UROSBridge, we need to create a service client class first. This class should extend the FROSBridgeSrvClient and implement the constructor and a callback function. Below is an example of service "AddTwoInts" client.  

```cpp
#pragma once
#include "ROSBridgeSrvClient.h"
#include "tutorial_srvs/AddTwoInts.h"
class FROSAddTwoIntsClient final : public FROSBridgeSrvClient
{
public:
    FROSAddTwoIntsClient(const FString& InName):
        FROSBridgeSrvClient(InName, TEXT("rospy_tutorials/AddTwoInts"))
    {          
    }

    void Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest, TSharedPtr<FROSBridgeSrv::SrvResponse> InResponse) override
    {
        // Downcast to convert InRequest and InResponse to corresponding types
        TSharedPtr<rospy_tutorials::AddTwoInts::Request> Request =
            StaticCastSharedPtr<rospy_tutorials::AddTwoInts::Request>(InRequest);
        TSharedPtr<rospy_tutorials::AddTwoInts::Response> Response =
            StaticCastSharedPtr<rospy_tutorials::AddTwoInts::Response>(InResponse);

        UE_LOG(LogTemp, Log, TEXT("Add Two Ints: %d + %d = %d"), Request->GetA(), Request->GetB(), Response->GetSum());
    }
};
```

Then in ROSActor, we can send service requests using the following function:

```cpp
TSharedPtr<FROSAddTwoIntsClient> ServiceClient =
    MakeShareable<FROSAddTwoIntsClient>(new FROSAddTwoIntsClient(TEXT("add_two_ints")));

int NumA = FMath::RandRange(1, 10000);
int NumB = FMath::RandRange(1, 10000);
TSharedPtr<FROSBridgeSrv::SrvRequest> Request = MakeShareable(new rospy_tutorials::AddTwoInts::Request(NumA, NumB));
// Create a request instance with request parameters
TSharedPtr<FROSBridgeSrv::SrvResponse> Response = MakeShareable(new rospy_tutorials::AddTwoInts::Response());
// Create an empty response instance
Handler->CallService(ServiceClient, Request, Response);
```

Notice: The `CallService` is not a blocking function, i.e. it will not block the main actor thread to wait for service response but it will call the callback function once it receives the response in following ticks.

#### Send Response to Service Requests

The plugin can also works as a "server" side who receives ros service requests from and returns response to the clients.

To process service requests in UROSBridge, we need to create a service server class first. This class should extend the FROSBridgeSrvServer and implement the constructor, `FromJson`, and `CallBack` function. It is very similar to ROS Bridge Subscriber classes but the only difference is that the return type of `CallBack` is `TSharedPtr<FROSBridgeSrv::SrvResponse>` rather than `void`. Below is an example of service AddTwoInts server.

```cpp
 #pragma once

 #include "ROSBridgeSrvServer.h"
 #include "tutorial_srvs/AddTwoInts.h"

 class FROSAddTwoIntsServer final : public FROSBridgeSrvServer
 {
 public:
     FROSAddTwoIntsServer(const FString& InName):
         FROSBridgeSrvServer(InName, TEXT("rospy_tutorials/AddTwoInts"))
     {

     }

     TSharedPtr<FROSBridgeSrv::SrvRequest> FromJson(TSharedPtr<FJsonObject> JsonObject) const override
     {
         TSharedPtr<rospy_tutorials::AddTwoInts::Request> Request =
             MakeShareable(rospy_tutorials::AddTwoInts::Request());
         Request->FromJson(JsonObject);
         return TSharedPtr<FROSBridgeSrv::SrvRequest>(Request);
     }

     TSharedPtr<FROSBridgeSrv::SrvResponse> Callback(TSharedPtr<FROSBridgeSrv::SrvRequest> InRequest) override
     {
         TSharedPtr<rospy_tutorials::AddTwoInts::Request> Request =
             StaticCastSharedPtr<rospy_tutorials::AddTwoInts::Request>(InRequest);

         int64 Sum = Request->GetA() + Request->GetB();
         UE_LOG(LogTemp, Log, TEXT("Service [%s] Server: Add Two Ints: %d + %d = %d"), *Name, Request->GetA(), Request->GetB(), Sum);
         return MakeShareable<FROSBridgeSrv::SrvResponse>
                   (new rospy_tutorials::AddTwoInts::Response(Sum));
     }

 }
```

In Actor, register the server to ROS bridge, then it will process incoming service requests automatically. After disconnection, the server will be automatically destroyed.

```cpp
void AROSActor::BeginPlay()
{
    Super::BeginPlay();

    // Set websocket server address to ws://127.0.0.1:9001
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(TEXT("127.0.0.1"), 9001));

    // Connect to ROSBridge Websocket server.
    Handler->Connect();

    // Add service clients and servers
    TSharedPtr<FROSAddTwoIntsServer> ServiceServer =
    MakeShareable<FROSAddTwoIntsServer>(new FROSAddTwoIntsServer(TEXT("add_two_ints")));
    Handler->AddServiceServer(ServiceServer);
}
```

#### Add More Message / Service Types

This plugin already has support for `std_msgs`, `geometry_msgs`, `std_srvs`, etc. but sometimes other types of message / service will be required. We can add new message classes to the plugin or directly to the project source folder.   

##### Message / Topic

Messages should extend the `FROSBridgeMsg` class, and implement the following functions:

- Constructor & Destructor
- `void FromJson(TSharedPtr<FJsonObject> JsonObject)`
    - set all the properties from the JsonObject
    - For numbers, use `JsonObject->GetNumberField(FieldName)`
    - For strings, use `JsonObject->GetStringField(FieldName)`
    - For other message types or ros time, use `ClassType::GetFromJson(JsonObject->GetObjectField(FieldName))`    
    - For array, first get JsonValue array using `TArray<TSharedPtr<FJsonValue>> PointsPtrArray = JsonObject->GetArrayField(TEXT("points"))`, then for each element `Ptr` in the array, call `Ptr->AsObject()`, `Ptr->AsNumber()` or `Ptr->AsString()` function to get its value.
    - It is recommended to always do type checking using Unreal `check(...)` macro
- `static CLASS_NAME GetFromJson(TSharedPtr<FJsonObject> JsonObject)`
    - the static version of FromJson()
    - Create a new message class and use `FromJson(JsonObject)` to set its properties
- `virtual FString ToString () const`
    - Create a string with all of the properties of this class for printing.
- `virtual TSharedPtr<FJsonObject> ToJsonObject() const`
    - Create an FJsonObject and save all of the properties of this message instance to the JsonObject.
    - For numbers, use `JsonObject->SetNumberField(FieldName, Value)`
    - For strings, use `JsonObject->SetStringField(FieldName, Value)`
    - For other message types or ros time, use `JsonObject->SetObjectField(FieldName, Field.ToJsonObject())`    
    - For arrays, we first create a JsonValue array using `TArray<TSharedPtr<FJsonValue>> PtrArray`, then add shared pointer to new created FJsonValueObject / FJsonValueNumber / FJsonValueString to the array, and finally set the field value to this array using `Object->SetArrayField(FieldName, PtrArray);`

There are several good examples to follow when writing message classes. `geometry_msgs/Vector3` is a message class with only built-in types; `geometry_msgs/Accel` is a message class which includes other messages; `geometry_msgs/Polygon` is a message class with arrays.

##### Services

Services consists of two parts, **request** and **response**, each of which is a ROS message class. In the plugin,  for each service we define a class extending to the `FROSBridgeSrv` base class, inside which we define `Request` and `Response` classes respectively extending to the `SrvRequest` and `SrvResponse` class. Like messages, in each class we need to implement `FromJson`, `ToString`, `ToJsonObject` and static `GetFromJson` method functions.
