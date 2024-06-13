// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_Reload.h"

#include "GGFShooterGameplayTags.h"

UGGFGA_Reload::UGGFGA_Reload()
{
    // AFireArm::Reload는 자체 RPC로 구현되어 있기 때문에 LocalOnly 정책을 사용합니다.
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;

    // 입력 태그
    InputTag = Input::Reload;

    // 태그 설정
    AbilityTags.AddLeafTag(Action::Reload);
    ActivationOwnedTags.AddLeafTag(Action::Reload);
}

void UGGFGA_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    GetFireArm()->OnReloadFinished.AddDynamic(this, &ThisClass::OnReloadFinished);
    GetFireArm()->Reload();
}

bool UGGFGA_Reload::InternalCanActivate()
{
    return Super::InternalCanActivate() && GetFireArm()->CanReload();
}

void UGGFGA_Reload::OnReloadFinished()
{
    GetFireArm()->OnReloadFinished.RemoveDynamic(this, &ThisClass::OnReloadFinished);
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
