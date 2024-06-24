using UnrealBuildTool;

public class GGFCombatSystem : ModuleRules
{
    public GGFCombatSystem(ReadOnlyTargetRules Target) : base(Target)
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
                "GGFCore",
                "GASExtension",
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
