// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameProject_2D : ModuleRules
{
	public GameProject_2D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
