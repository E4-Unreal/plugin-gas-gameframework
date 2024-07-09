using UnrealBuildTool;

public class GGFPlayerSystem : ModuleRules
{
    public GGFPlayerSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "EnhancedInput",
                "UMG",
                "AIModule",

                // GAS
                "GameplayAbilities",

                // GASGameFramework
                "GGFCore",
                "GGFWidgetSystem"
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
