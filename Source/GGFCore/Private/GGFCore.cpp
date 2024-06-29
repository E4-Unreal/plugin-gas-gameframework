#include "GGFCore.h"

#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "GGFCoreSetting.h"
#include "Developer/Settings/Public/ISettingsModule.h"

#if WITH_EDITOR
#include "PropertyEditorModule.h"
#endif

IMPLEMENT_MODULE(FGGFCoreModule, GGFCore)

#define LOCTEXT_NAMESPACE "FGGFCoreModule"

void FGGFCoreModule::StartupModule()
{
    // GAS를 위한 설정
    InitializeForGameplayAbilitySystem();

    if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->RegisterSettings("Project", "Plugins", "GGFCore",
            LOCTEXT("RuntimeSettingsName", "GGFCore"), LOCTEXT("RuntimeSettingsDescription", "Setting for GGFCore"),
            GetMutableDefault<UGGFCoreSetting>());
    }

#if WITH_EDITOR
    // 디테일 패널에 커스텀 섹션 추가
    RegisterSectionMappings();
#endif
}

void FGGFCoreModule::ShutdownModule()
{
    if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "GGFCore");
    }
}

void FGGFCoreModule::InitializeForGameplayAbilitySystem()
{
    // AbilitySystemGlobals
    UAbilitySystemGlobals& AbilitySystemGlobals = UAbilitySystemGlobals::Get();

    // TargetData 오류 방지
    AbilitySystemGlobals.InitGlobalData();

    // 디버그 설정
    AbilitySystemGlobals.bUseDebugTargetFromHud = true;

    // GameplayCue 경로 추가
    UGameplayCueManager* GameplayCueManager = AbilitySystemGlobals.GetGameplayCueManager();
    GameplayCueManager->AddGameplayCueNotifyPath("/GASGameFramework");
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
