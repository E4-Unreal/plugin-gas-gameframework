// Fill out your copyright notice in the Description page of Project Settings.


#include "GEGameplayAbilityBase.h"

#include "GEHealthAttributeSet.h"

UGEGameplayAbilityBase::UGEGameplayAbilityBase()
{
    // 기본 인스턴싱 정책 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 기본 Blocking 태그 설정
    ActivationBlockedTags.AddTag(GEGameplayTags::DeadTag);
}

void UGEGameplayAbilityBase::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    if(bActivateAbilityOnGranted)
    {
        ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
    }
}
