# UROSBridge

A UE4 Plugin for communication with ROS Bridge using WebSockets, which supports subscribing and publishing both ROS messages (topics) and services. 

This plugin is originated from Michael Jenkin and Mathias Ciarlo's [ROSBridgeLib](https://github.com/MathiasCiarlo/ROSBridgeLib), a Unity-based ROS bridge library; This repository could be used as a plugin for UE4 or UE4 projects. 

## Messages and Services

Now only `std_msgs`, `sensor_msgs`, `geometry_msgs` and `std_srvs` are supported. If you are going to add new message / service types, please make a pull request. 

## Usage 

See [this documentation](https://github.com/robcog-iai/RobCoG/tree/robosim/Documentation) for tutorials on how to subscribe to topic, publish to topic, call external services and advertise to service calls. 

[ROSBridgeTest](https://github.com/robcog-iai/RobCoG/tree/robosim) is an Unreal Project to test all these functionalities.

To add new message / service classes, please refer to `Source/UROSBridge/Public` directory. 

See [here](https://github.com/gnoliyil/pr2_kinetic_packages/tree/e43479ea6088062b63271c6b94417c266429d439) PR2 Packages for ROS Kinetic Kame.

## Todo

## Note

This library uses [libwebsockets](http://libwebsockets.org/) as the WebSocket library and uses the WebSocket UE4 Wrapper from [HTML5Networking](https://github.com/ankitkk/HTML5Networking) Plugin. 
