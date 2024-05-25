using UnrealBuildTool;

public class GGFCharacterSystem : ModuleRules
{
    public GGFCharacterSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",

                // 입력
                "EnhancedInput",

                // UI
                "UMG",

                // GAS
                "GameplayTags",
                "GameplayTasks",
                "GameplayAbilities",

                // GASGameFramework
                "GASExtension",
                "GGFInteractionSystem",
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
