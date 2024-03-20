// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireArm/GEGA_Fire.h"

#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Equipment/Components/GEEquipmentManager.h"
#include "Weapon/FireArm/GEFireArm.h"

UGEGA_Fire::UGEGA_Fire()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;
}

void UGEGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

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

void UGEGA_Fire::OnRelease_Event(float TimeHeld)
{
    if(!FireTimer.IsValid()) return;

    if(const UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(FireTimer);
        FireTimer.Invalidate();
    }

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
