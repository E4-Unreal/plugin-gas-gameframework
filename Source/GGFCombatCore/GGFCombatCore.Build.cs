using UnrealBuildTool;

public class GGFCombatCore : ModuleRules
{
    public GGFCombatCore(ReadOnlyTargetRules Target) : base(Target)
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

                // GASGameFramework
                "GGFDataSystem"
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
