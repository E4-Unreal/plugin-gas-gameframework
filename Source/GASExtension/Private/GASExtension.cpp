#include "GASExtension.h"

#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"

#define LOCTEXT_NAMESPACE "FGASExtensionModule"

void FGASExtensionModule::StartupModule()
{
    // GAS를 위한 설정
    InitializeForGameplayAbilitySystem();
}

void FGASExtensionModule::ShutdownModule()
{

}

void FGASExtensionModule::InitializeForGameplayAbilitySystem()
{
    // AbilitySystemGlobals
    UAbilitySystemGlobals& AbilitySystemGlobals = UAbilitySystemGlobals::Get();

    // TargetData 오류 방지
    AbilitySystemGlobals.InitGlobalData();

    // 디버그 설정
    AbilitySystemGlobals.bUseDebugTargetFromHud = true;

    // GameplayCue 경로 추가
    UGameplayCueManager* GameplayCueManager = AbilitySystemGlobals.GetGameplayCueManager();
    GameplayCueManager->AddGameplayCueNotifyPath("/GASExtension");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGASExtensionModule, GASExtension)
