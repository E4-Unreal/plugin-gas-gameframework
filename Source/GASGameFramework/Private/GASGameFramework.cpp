// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASGameFramework.h"

#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "GASExtensionSetting.h"

IMPLEMENT_MODULE(FGASGameFrameworkModule, GASGameFramework)

#define LOCTEXT_NAMESPACE "FGASGameFrameworkModule"

void FGASGameFrameworkModule::StartupModule()
{
    // GAS를 위한 설정
    InitializeForGameplayAbilitySystem();

    // 설정 리로드
    ReloadConfigs();
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

void FGASGameFrameworkModule::ReloadConfigs()
{
    // GASExtension (다른 모듈에서 선언된 NativeGameplayTag 갱신)
    auto GASExtensionSetting = GetMutableDefault<UGASExtensionSetting>();
    GASExtensionSetting->LoadConfig();
}

#undef LOCTEXT_NAMESPACE
