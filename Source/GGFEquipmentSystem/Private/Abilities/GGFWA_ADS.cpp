// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GGFWA_ADS.h"

#include "GGFWeapon.h"
#include "Abilities/AbilityTask_SetCameraFOV.h"
#include "Interfaces/GGFCameraInterface.h"

bool UGGFWA_ADS::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
    FGameplayTagContainer* OptionalRelevantTags) const
{
    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)
    && GetAvatarActorFromActorInfo()->Implements<UGGFCameraInterface>()
    && GetWeapon()->Implements<UGGFCameraInterface>();
}

void UGGFWA_ADS::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    const AActor* CachedWeapon = GetWeapon();
    AbilityTask = UAbilityTask_SetCameraFOV::SetCameraFOV(this, IGGFCameraInterface::Execute_GetFieldOfView(CachedWeapon), IGGFCameraInterface::Execute_GetInterpSpeed(CachedWeapon));
    AbilityTask->ReadyForActivation();
}

void UGGFWA_ADS::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
    Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

    AbilityTask->EndTask();
    AbilityTask = UAbilityTask_SetCameraFOV::SetCameraFOV(this, IGGFCameraInterface::Execute_GetFieldOfView(GetAvatarActorFromActorInfo()), IGGFCameraInterface::Execute_GetInterpSpeed(GetWeapon()));
    AbilityTask->ReadyForActivation();
    AbilityTask->OnEnd.AddDynamic(this,  &ThisClass::EndAbilityImmediately);
}

void UGGFWA_ADS::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo)
{
    if(bIsActive) CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

void UGGFWA_ADS::EndAbilityImmediately()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
