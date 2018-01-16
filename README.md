# UROSBridge

Unereal ROS bridge plugin for communication with [rosbridge](http://wiki.ros.org/rosbridge_suite) using WebSockets. The plugin supports subscribing and publishing both ROS messages (topics) and services.

## Messages and Services

Most standard ros msgs are supported (`std_msgs`, `sensor_msgs`, `geometry_msgs`, `std_srvs` etc.). If you are going to add new message / service types, please make a pull request. To add new message / service classes, please refer to `Source/UROSBridge/Public` directory (see [here](Source/UROSBridge/Public/)).

## Usage

* [Tutorials](Documentation/Examples.md) on how to subscribe to topic, publish to topic, call external services and advertise to service calls.

* See the [ex-ros-tf-robosim](https://github.com/robcog-iai/RobCoG/tree/ex-ros-tf-robosim) branch of RobCoG as an Unreal Project example to test all these functionalities.

#### How to include the plugin

-   Add the plugin to your project (e.g `MyProject/Plugins/UROSBridge`)      

-   Add the module dependency to your module (Project, Plugin); In the
    `MyModule.Build.cs` file:  

		PublicDependencyModuleNames.AddRange(  
		new string[]  
		{  
		...  
		"UROSBridge",
		"Json",
		"JsonUtilities",
		...  
		}  
		);  

#### Other projects using UROSBridge:

 * [UROSActorControl](https://github.com/bbferka/UROSActorControl)

## Credits

* This library uses [libwebsockets](http://libwebsockets.org/) as the WebSocket library and uses the WebSocket UE4 Wrapper from [HTML5Networking](https://github.com/ankitkk/HTML5Networking) Plugin.

* This plugin is originated from Michael Jenkin and Mathias Ciarlo's [ROSBridgeLib](https://github.com/MathiasCiarlo/ROSBridgeLib), a Unity-based ROS bridge library;

* Thanks to [Yilong Li](https://github.com/gnoliyil) for the contributions during the Google Summer of Code 2017.

### Engine Version 4.18
