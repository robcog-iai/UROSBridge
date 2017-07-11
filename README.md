# ROSBridgePlugin

A UE4 Plugin for communication with ROS Bridge using WebSockets. 

This plugin is originated from Michael Jenkin and Mathias Ciarlo's [ROSBridgeLib](https://github.com/MathiasCiarlo/ROSBridgeLib), a Unity-based ROS bridge library; This repository could be used as a plugin for UE4 or UE4 projects. 

## Messages 

Now only `std_msgs` are supported and We are intending to add more messages like `sensor_msgs` and `geometry_msgs` for PR2 simulation. 

## Usage 

To subscribe messages, the user needs to extend a subscriber class from FROSBridgeSubscriber, and implement its destructor, `ParseMessage` and `CallBack` methods. 

To publish messages, the user needs to extend a publisher class from FROSBridgePublisher or use FROSBridgePublisher directly. 

Example: 

``` cpp
UCLASS()
class ROSBRIDGETEST_API AROSBridgeTestGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
	
public:
    FROSBridgeHandler* Handler;
    FROSStringSubScriber* Subscriber;
    FROSBridgePublisher* Publisher;

    AROSBridgeTestGameModeBase(const FObjectInitializer &ObjectInitializer) :
        AGameModeBase(ObjectInitializer){
        PrimaryActorTick.bCanEverTick = true;
        PrimaryActorTick.bStartWithTickEnabled = true;
    }

    void BeginPlay() override
    {
        Super::BeginPlay();
        // Create ROS Bridge Handler
        Handler = new FROSBridgeHandler(TEXT("127.0.0.1"), 9001);

        // Create ROS Subscriber, which extends the ROSBridgeSubscriber class
        Subscriber = new FROSStringSubScriber(TEXT("/chatter")); 
        Handler->AddSubscriber(Subscriber);

        // Create ROS Publisher
        Publisher = new FROSBridgePublisher(TEXT("std_msgs/String"), TEXT("/talker"));
        Handler->AddPublisher(Publisher);

        Handler->Connect();
    }

    void Tick(float DeltaSeconds) override {
        Super::Tick(DeltaSeconds);
 
        // Test sending message
        FROSBridgeMsgStdmsgsString* StringMsgToSend = new
            FROSBridgeMsgStdmsgsString(TEXT("New Message at ") + FDateTime::Now().ToString());
        Handler->PublishMsg(TEXT("/talker"), StringMsgToSend);
        delete StringMsgToSend;

        // Process message received between two frames
        Handler->Render();
    }

    void Logout(AController *Exiting) override
    {
        // disconnect the handler
        Handler->Disconnect();

        // delete used handler, subscriber and publisher. 
        delete Handler;
        delete Subscriber;
        delete Publisher;

        // game ends. 
        AGameModeBase::Logout(Exiting);
    }

};
```

## TODO

The library is currently not blueprintable so it could be only used in C++ codes. We need to add UHT-related macros (`UCLASS`, `UFUNCTION`, etc.) to make it work in blueprints.

## Note

This library uses [libwebsockets](http://libwebsockets.org/) as the WebSocket library and uses the WebSocket UE4 Wrapper from [HTML5Networking](https://github.com/ankitkk/HTML5Networking) Plugin. 
