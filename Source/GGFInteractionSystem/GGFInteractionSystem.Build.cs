using UnrealBuildTool;

public class GGFInteractionSystem : ModuleRules
{
    public GGFInteractionSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",

                // UI
                "UMG",

                // 향상된 입력
                "EnhancedInput",

                // GAS
                "GameplayTags",
                "GameplayTasks",
                "GameplayAbilities",

                // GASExtension
                "GGFCore"
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
