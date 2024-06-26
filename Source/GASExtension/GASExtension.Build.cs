﻿using UnrealBuildTool;

public class GASExtension : ModuleRules
{
    public GASExtension(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",

                // 입력
                "EnhancedInput",

                // GAS
                "GameplayTags",
                "GameplayTasks",
                "GameplayAbilities",

                // 물리
                "PhysicsCore"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
    }
}
