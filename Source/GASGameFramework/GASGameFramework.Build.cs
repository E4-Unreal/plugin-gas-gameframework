// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASGameFramework : ModuleRules
{
	public GASGameFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                // Default
				"Core",
                "EnhancedInput",

                // UI
                "UMG",

                // 이펙트
                "Niagara",
                "PhysicsCore",

                // GAS
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
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
