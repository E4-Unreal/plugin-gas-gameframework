// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GGFGA_ApplyEffectsToSelf.h"

#include "AbilitySystemComponent.h"
#include "GEBlueprintFunctionLibrary.h"

void UGGFGA_ApplyEffectsToSelf::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // GameplayEffects 적용
    UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(EffectsToApply, ActorInfo->AbilitySystemComponent.Get());

    // Ability 종료
    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
