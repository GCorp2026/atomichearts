// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class atomichearts : ModuleRules
{
	public atomichearts(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"atomichearts",
			"atomichearts/Variant_Platforming",
			"atomichearts/Variant_Platforming/Animation",
			"atomichearts/Variant_Combat",
			"atomichearts/Variant_Combat/AI",
			"atomichearts/Variant_Combat/Animation",
			"atomichearts/Variant_Combat/Gameplay",
			"atomichearts/Variant_Combat/Interfaces",
			"atomichearts/Variant_Combat/UI",
			"atomichearts/Variant_SideScrolling",
			"atomichearts/Variant_SideScrolling/AI",
			"atomichearts/Variant_SideScrolling/Gameplay",
			"atomichearts/Variant_SideScrolling/Interfaces",
			"atomichearts/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
