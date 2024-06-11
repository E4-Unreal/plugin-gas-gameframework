#include "GGFCore.h"

#if WITH_EDITOR
#include "PropertyEditorModule.h"
#endif

IMPLEMENT_MODULE(FGGFCoreModule, GGFCore)

#define LOCTEXT_NAMESPACE "FGGFCoreModule"

void FGGFCoreModule::StartupModule()
{
#if WITH_EDITOR
    // 디테일 패널에 커스텀 섹션 추가
    RegisterSectionMappings();
#endif
}

void FGGFCoreModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "Custom Detail"
void FGGFCoreModule::RegisterSectionMappings()
{
    static const FName PropertyEditor("PropertyEditor");
    FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);

    // Actor
    {
        {
            // Config, 설정
            const TSharedRef<FPropertySection> ActorConfigSection = PropertyModule.FindOrCreateSection("Actor", "Config", LOCTEXT("Config", "설정"));
            ActorConfigSection->AddCategory("Config");
        }

        {
            // State, 상태
            const TSharedRef<FPropertySection> ActorConfigSection = PropertyModule.FindOrCreateSection("Actor", "State", LOCTEXT("State", "상태"));
            ActorConfigSection->AddCategory("State");
        }

        {
            // Reference, 레퍼런스
            const TSharedRef<FPropertySection> ActorConfigSection = PropertyModule.FindOrCreateSection("Actor", "Reference", LOCTEXT("Reference", "레퍼런스"));
            ActorConfigSection->AddCategory("Reference");
        }
    }

    // ActorComponent
    {
        {
            // Config, 설정
            const TSharedRef<FPropertySection> ActorComponentConfigSection = PropertyModule.FindOrCreateSection("ActorComponent", "Config", LOCTEXT("Config", "설정"));
            ActorComponentConfigSection->AddCategory("Config");
        }

        {
            // State, 상태
            const TSharedRef<FPropertySection> ActorComponentConfigSection = PropertyModule.FindOrCreateSection("ActorComponent", "State", LOCTEXT("State", "상태"));
            ActorComponentConfigSection->AddCategory("State");
        }

        {
            // Reference, 레퍼런스
            const TSharedRef<FPropertySection> ActorComponentConfigSection = PropertyModule.FindOrCreateSection("ActorComponent", "Reference", LOCTEXT("Reference", "레퍼런스"));
            ActorComponentConfigSection->AddCategory("Reference");
        }
    }
}
#undef LOCTEXT_NAMESPACE
#endif
