// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_AutoActivatable.h"

#include "AbilitySystemComponent.h"

void UGGFGA_AutoActivatable::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    // AbilitySystemComponent 획득
    UAbilitySystemComponent* AbilitySystem = ActorInfo->AbilitySystemComponent.Get();

    // AbilitySpec 획득 및 유효성 검사
    FGameplayAbilitySpec* FoundSpec = AbilitySystem->FindAbilitySpecFromHandle(Spec.Handle);
    if(FoundSpec == nullptr) return;

    // Ability 제거 옵션 설정
    FoundSpec->RemoveAfterActivation = bRemoveAfterActivation;

    // Ability 발동
    if(bActivateAbilityOnGranted)
    {
        if (!AbilitySystem->InternalTryActivateAbility(Spec.Handle) && bRemoveAfterActivation)
        {
            // 발동 실패 시 즉시 제거
            AbilitySystem->ClearAbility(Spec.Handle);
        }
    }
}
