using UnrealBuildTool;

public class GGFShooterCore : ModuleRules
{
    public GGFShooterCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",

                // UI
                "UMG",

                // 이펙트
                "Niagara",
                "PhysicsCore",

                // GAS
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",

                // GASGameFramework
                "GGFCore",
                "GGFDataSystem",
                "GGFEquipmentSystem",
                "GGFCombatSystem",
                "GGFInteractionSystem",
                "GGFEffectSystem"
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
