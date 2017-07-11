# ROSBridgePlugin

A UE4 Plugin for communication with ROS Bridge. 

This plugin is originated from Michael Jenkin and Mathias Ciarlo's [ROSBridgeLib](https://github.com/MathiasCiarlo/ROSBridgeLib), a Unity-based ROS bridge library; This repository could be used as a plugin for UE4 or UE4 projects. 

## Messages 

Now only `std_msgs` are supported and We are intending to add more messages like `sensor_msgs` and `geometry_msgs` for PR2 simulation. 

## Usage 

To subscribe messages, the user needs to extend a subscriber class from FROSBridgeSubscriber, and implement its destructor, `ParseMessage` and `CallBack` methods. 

To publish messages, the user needs to extend a publisher class from FROSBridgePublisher or use FROSBridgePublisher directly. 

## TODO

The library is currently not blueprintable so it could be only used in C++ codes. We need to add UHT-related macros (`UCLASS`, `UFUNCTION`, etc.) to make it work in blueprints.
