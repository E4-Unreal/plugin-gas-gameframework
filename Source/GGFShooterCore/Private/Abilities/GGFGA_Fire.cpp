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
    AbilityTags.AddLeafTag(GEGameplayTags::Action::Attack);
    ActivationOwnedTags.AddLeafTag(GEGameplayTags::Action::Attack);
}

void UGGFGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // Cost 지불
    if(!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

    // 총기 레퍼런스 가져오기
    AGGFFireArm* CachedFireArm = GetFireArm();

    // 즉시 발사
    CachedFireArm->Fire();

    // TODO 발사 모드 확인을 위한 변수가 필요
    // 연사
    if(const UWorld* World = CachedFireArm->GetWorld())
    {
        World->GetTimerManager().SetTimer(
            FireTimer,
            FTimerDelegate::CreateUObject(CachedFireArm, &AGGFFireArm::Fire),
            CachedFireArm->GetFireInterval(),
            true);
    }
}

void UGGFGA_Fire::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // 발사 중지
    StopFire();
}

bool UGGFGA_Fire::InternalCanActivate()
{
    return Super::InternalCanActivate() && GetFireArm()->CanFire();
}

void UGGFGA_Fire::StopFire()
{
    if(!FireTimer.IsValid()) return;

    if(const UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(FireTimer);
        FireTimer.Invalidate();
    }
}
