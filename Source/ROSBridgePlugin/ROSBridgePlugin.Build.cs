// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ROSBridgePlugin : ModuleRules
	{
		public ROSBridgePlugin (TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					"ROSBridgePlugin/Public"
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
                    "ROSBridgePlugin/Public",
					"ROSBridgePlugin/Private"
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
                    "Core", "CoreUObject",
					"Networking", "Sockets", "PacketHandler",
                    "libWebSockets", "OpenSSL", "zlib",
                    "Json", "JsonUtilities"
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "CoreUObject", 
                    "Engine",
                    "Core",
                    "Networking", "Sockets", "PacketHandler",
                    "libWebSockets", "OpenSSL", "zlib",
                    "Json", "JsonUtilities"
                }
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
				}
				);
		}
	}
}
