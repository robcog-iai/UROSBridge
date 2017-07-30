# ROSBridgePlugin

A UE4 Plugin for communication with ROS Bridge using WebSockets, which supports subscribing and publishing both ROS messages (topics) and services. 

This plugin is originated from Michael Jenkin and Mathias Ciarlo's [ROSBridgeLib](https://github.com/MathiasCiarlo/ROSBridgeLib), a Unity-based ROS bridge library; This repository could be used as a plugin for UE4 or UE4 projects. 

## Messages and Services

Now only `std_msgs`, `sensor_msgs`, `geometry_msgs` and `std_srvs` are supported. If you are going to add new message / service types, please make a pull request. 

## Usage 

See [Wiki](https://github.com/gnoliyil/ROSBridgePlugin/wiki) for tutorials on how to subscribe to topic, publish to topic, call external services and advertise to service calls. 

[ROSBridgeTest](https://github.com/gnoliyil/URoboSim/tree/RI/ROSBridgeTest) is an Unreal Project to test all these functionalities.

To add new message / service classes, please refer to `Source/ROSBridgePlugin/Public` directory. 

## TODO

1. Use smart pointers instead of C++ native pointers. 

2. The library is currently not blueprintable so it could be only used in C++ codes. We need to add UHT-related macros (`UCLASS`, `UFUNCTION`, etc.) to make it work in blueprints.

## Note

This library uses [libwebsockets](http://libwebsockets.org/) as the WebSocket library and uses the WebSocket UE4 Wrapper from [HTML5Networking](https://github.com/ankitkk/HTML5Networking) Plugin. 
