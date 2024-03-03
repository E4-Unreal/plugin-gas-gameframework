// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GEGA_ApplyEffectsToSelf.h"

#include "AbilitySystemComponent.h"
#include "FunctionLibraries/GEFunctionLibrary.h"

void UGEGA_ApplyEffectsToSelf::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // GameplayEffects 적용
    UGEFunctionLibrary::ApplyGameplayEffectsToSystem(EffectsToApply, ActorInfo->AbilitySystemComponent.Get());

    // Ability 종료
    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
