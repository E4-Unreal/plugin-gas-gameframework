using UnrealBuildTool;

public class TPSSample : ModuleRules
{
    public TPSSample(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",

                // GAS
                "GameplayTags",
                "GameplayTasks",
                "GameplayAbilities",

                // GAS GameFramework 플러그인
                "GGFCore",
                "GASExtension",
                "GGFAnimationSystem",
                "GASGameFramework",
                "GGFCharacterSystem",
                "GGFEquipmentSystem"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",

                // 애니메이션
                "AnimGraphRuntime"
            }
        );
    }
}
