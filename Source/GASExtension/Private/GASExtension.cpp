#include "GASExtension.h"

#include "AbilitySystemGlobals.h"

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
    AbilitySystemGlobals.AddGameplayCueNotifyPath("/GASExtension");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGASExtensionModule, GASExtension)
