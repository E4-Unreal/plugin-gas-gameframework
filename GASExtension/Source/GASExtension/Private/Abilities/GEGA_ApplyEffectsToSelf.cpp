// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GEGA_ApplyEffectsToSelf.h"

#include "AbilitySystemComponent.h"

void UGEGA_ApplyEffectsToSelf::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // AbilitySystemComponent 획득
    UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get();

    for (const auto& EffectClass : EffectsToApply)
    {
        // 유효성 검사
        if(EffectClass == nullptr) continue;

        // Ability 발동 주체에 GameplayEffect 적용
        FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystem->MakeOutgoingSpec(EffectClass, 0, MakeEffectContext(Handle, ActorInfo));
        if(GameplayEffectSpecHandle.IsValid())
        {
            AbilitySystem->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
        }
    }

    // Ability 종료
    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
