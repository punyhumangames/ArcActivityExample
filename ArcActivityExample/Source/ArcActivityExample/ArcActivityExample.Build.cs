// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArcActivityExample : ModuleRules
{
	public ArcActivityExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput",
			"ArcActivitiesPlugin",
			"GameplayTags",
			"UMG",
			"NetCore",
		});
	}
}
