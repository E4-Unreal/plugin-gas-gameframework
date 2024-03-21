﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/GECharacterState.h"

#include "GEGameplayTags.h"
#include "GameFramework/Character.h"

UGECharacterState::UGECharacterState()
{
    // 기본 인스턴싱 정책 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 블록 태그 기본 설정
    BlockAbilitiesWithTag.AddTagFast(GEGameplayTags::State::DeadTag); // Dead 상태를 작성할 때는 제외해야 합니다.
    BlockAbilitiesWithTag.AddTagFast(GEGameplayTags::State::KnockdownTag);
    BlockAbilitiesWithTag.AddTagFast(GEGameplayTags::State::StunTag);
}

void UGECharacterState::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // State Enter
    if(ACharacter* AvatarCharacter = Cast<ACharacter>(ActorInfo->AvatarActor))
        OnEnter(AvatarCharacter);
}

void UGECharacterState::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // State Exit
    if(ACharacter* AvatarCharacter = Cast<ACharacter>(ActorInfo->AvatarActor))
        OnExit(AvatarCharacter);
}

void UGECharacterState::OnEnter_Implementation(ACharacter* AvatarCharacter)
{
}

void UGECharacterState::OnExit_Implementation(ACharacter* AvatarCharacter)
{
}