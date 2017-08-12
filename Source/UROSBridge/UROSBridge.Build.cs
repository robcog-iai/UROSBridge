// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

using UnrealBuildTool;

public class UROSBridge : ModuleRules
{
	public UROSBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
            new string[] {
                "UROSBridge/Public"
                // ... add public include paths required here ...
            });

        PrivateIncludePaths.AddRange(
            new string[] {
	            "UROSBridge/Public",
                "UROSBridge/Private"
                // ... add other private include paths required here ...
            });

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
		        "Core", "CoreUObject",
                "Networking", "Sockets", "PacketHandler",
                "libWebSockets", "OpenSSL", "zlib",
                "Json", "JsonUtilities"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
	            "Core","Networking", "Sockets", "PacketHandler",
                "libWebSockets", "OpenSSL", "zlib",
                "Json", "JsonUtilities"
            });

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
            });
    }
}
