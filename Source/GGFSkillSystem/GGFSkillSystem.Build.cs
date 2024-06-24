﻿using UnrealBuildTool;

public class GGFSkillSystem : ModuleRules
{
    public GGFSkillSystem(ReadOnlyTargetRules Target) : base(Target)
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

                // GASGameFramework
                "GGFCore",
                "GASExtension",
                "GGFDataSystem",
                "GGFCharacterSystem",
                "GGFCombatSystem",
                "GGFEquipmentSystem",
                "GGFShooterCore"
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
