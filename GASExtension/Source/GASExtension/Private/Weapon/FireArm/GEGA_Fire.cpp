// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireArm/GEGA_Fire.h"

#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Equipment/Components/GEEquipmentManager.h"
#include "Weapon/FireArm/GEFireArm.h"

UGEGA_Fire::UGEGA_Fire()
{
    // AFireArm::Fire는 RPC로 구현되어 있기 때문에 LocalOnly 정책을 사용합니다.
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;

    /* 태그 설정 */
    using namespace GEGameplayTags;

    AbilityTags.AddLeafTag(Action::Attack);
    ActivationOwnedTags.AddLeafTag(Action::Attack);
}

void UGEGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // Cost 지불
    if(!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

    // 총기 레퍼런스 가져오기
    if(!CachedFireArm.IsValid())
    {
        if(UGEEquipmentManager* EquipmentManager = ActorInfo->AvatarActor->GetComponentByClass<UGEEquipmentManager>())
        {
            CachedFireArm = Cast<AGEFireArm>(EquipmentManager->GetSelectedEquipment());
            if(!CachedFireArm.IsValid()) CancelAbility(Handle, ActorInfo, ActivationInfo, true);
        }
        else
        {
            CancelAbility(Handle, ActorInfo, ActivationInfo, true);
        }
    }

    // 즉시 발사
    CachedFireArm->Fire();

    // TODO 발사 모드 확인을 위한 변수가 필요
    // 연사
    if(const UWorld* World = CachedFireArm->GetWorld())
    {
        World->GetTimerManager().SetTimer(
            FireTimer,
            FTimerDelegate::CreateUObject(CachedFireArm.Get(), &AGEFireArm::Fire),
            CachedFireArm->GetFireInterval(),
            true);

        UAbilityTask_WaitInputRelease* Task = UAbilityTask::NewAbilityTask<UAbilityTask_WaitInputRelease>(this);
        Task->OnRelease.AddDynamic(this, &ThisClass::OnRelease_Event);
        Task->ReadyForActivation();
    }
}

void UGEGA_Fire::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    StopFire();
}

void UGEGA_Fire::StopFire()
{
    if(!FireTimer.IsValid()) return;

    if(const UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(FireTimer);
        FireTimer.Invalidate();
    }
}

void UGEGA_Fire::OnRelease_Event(float TimeHeld)
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
