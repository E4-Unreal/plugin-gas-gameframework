// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_Fire.h"

#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "GEGameplayTags.h"
#include "GGFShooterGameplayTags.h"
#include "Weapons/GGFFireArm.h"

UGGFGA_Fire::UGGFGA_Fire()
{
    // AFireArm::Fire는 RPC로 구현되어 있기 때문에 LocalOnly 정책을 사용합니다.
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;

    // 입력 태그
    InputTag = Input::Fire;

    // 태그 설정
    AbilityTags.AddLeafTag(Action::Attack);
    ActivationOwnedTags.AddLeafTag(Action::Attack);
}

void UGGFGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // Cost 지불
    if(!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

    // 총기 레퍼런스 가져오기
    AGGFFireArm* CachedFireArm = GetFireArm();
    const auto& FireArmData = CachedFireArm->GetFireArmData();

    // 즉시 발사
    CachedFireArm->Fire();

    // 연사 모드 확인
    if(FireArmData.bAutomatic)
    {
        CachedFireArm->GetWorldTimerManager().SetTimer(
            FireTimer,
            this,
            &ThisClass::OnFire,
            CachedFireArm->GetFireInterval(),
            true);
    }
}

void UGGFGA_Fire::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    // 발사 중지
    StopFire();

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UGGFGA_Fire::InternalCanActivate()
{
    return Super::InternalCanActivate() && GetFireArm()->CanFire();
}

void UGGFGA_Fire::OnFire()
{
    auto CachedFireArm = GetFireArm();
    if(CachedFireArm->CanFire())
    {
        CachedFireArm->Fire();
    }
    else
    {
        EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
    }
}

void UGGFGA_Fire::StopFire()
{
    auto& WorldTimeManager = GetFireArm()->GetWorldTimerManager();
    if(WorldTimeManager.IsTimerActive(FireTimer))
    {
        WorldTimeManager.ClearTimer(FireTimer);
    }
}
