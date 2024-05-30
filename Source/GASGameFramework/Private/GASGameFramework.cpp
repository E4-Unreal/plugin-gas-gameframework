// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASGameFramework.h"

#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"

#if WITH_EDITOR
#include "PropertyEditorModule.h"
#endif

IMPLEMENT_MODULE(FGASGameFrameworkModule, GASGameFramework)

#define LOCTEXT_NAMESPACE "FGASGameFrameworkModule"

void FGASGameFrameworkModule::StartupModule()
{
    // GAS를 위한 설정
    InitializeForGameplayAbilitySystem();

#if WITH_EDITOR
    // 디테일 패널에 커스텀 섹션 추가
    RegisterSectionMappings();
#endif
}

void FGASGameFrameworkModule::ShutdownModule()
{

}

void FGASGameFrameworkModule::InitializeForGameplayAbilitySystem()
{
    // AbilitySystemGlobals
    UAbilitySystemGlobals& AbilitySystemGlobals = UAbilitySystemGlobals::Get();

    // GameplayCue 경로 추가
    UGameplayCueManager* GameplayCueManager = AbilitySystemGlobals.GetGameplayCueManager();
    GameplayCueManager->AddGameplayCueNotifyPath("/GASGameFramework");
}

#undef LOCTEXT_NAMESPACE

#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "Custom Detail"
void FGASGameFrameworkModule::RegisterSectionMappings()
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
    }
}
#undef LOCTEXT_NAMESPACE
#endif
