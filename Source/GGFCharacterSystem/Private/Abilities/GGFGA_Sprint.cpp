// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_Sprint.h"

#include "GGFCharacterGameplayTags.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGGFGA_Sprint::UGGFGA_Sprint()
{
    // 입력 태그 설정
    InputTag = Input::Sprint;

    // 상태 태그 설정
    ActivationOwnedTags.RemoveTag(Action::Root);
    ActivationOwnedTags.AddTagFast(State::Locomotion::Sprinting);
}

void UGGFGA_Sprint::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    AvatarCharacterMovement = GetAvatarCharacter()->GetCharacterMovement();
}

void UGGFGA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 캐릭터 최대 걷기 속도 증가
    UCharacterMovementComponent* CharacterMovement = GetAvatarCharacterMovement();
    DefaultMaxWalkSpeed = CharacterMovement->MaxWalkSpeed;
    CharacterMovement->MaxWalkSpeed = DefaultMaxWalkSpeed * MoveSpeedRatio;
}

void UGGFGA_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    // 캐릭터 최대 걷기 속도 복원
    UCharacterMovementComponent* CharacterMovement = GetAvatarCharacterMovement();
    CharacterMovement->MaxWalkSpeed = DefaultMaxWalkSpeed;

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
