// Copyright 2018, Institute for Artificial Intelligence - University of Bremen

using System.IO;
using UnrealBuildTool;

public class UROSBridge : ModuleRules
{
	public UROSBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
        	PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        	PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Sockets"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Core",
				"Networking",
				"PacketHandler",
				"libWebSockets",
				"OpenSSL",
				"zlib",				
				"Json",
				"JsonUtilities",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
