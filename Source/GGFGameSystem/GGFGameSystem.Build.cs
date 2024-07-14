using UnrealBuildTool;

public class GGFGameSystem : ModuleRules
{
    public GGFGameSystem(ReadOnlyTargetRules Target) : base(Target)
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
