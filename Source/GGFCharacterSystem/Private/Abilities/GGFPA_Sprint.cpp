// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFPA_Sprint.h"

#include "GGFCharacterGameplayTags.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UGGFPA_Sprint::UGGFPA_Sprint()
{
    // 입력 태그 설정
    InputTag = GGFGameplayTags::Input::Sprint;

    // 상태 태그 설정
    ActivationOwnedTags.AddTagFast(GGFGameplayTags::State::Sprinting);
}

bool UGGFPA_Sprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
    const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    ACharacter* AvatarCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) && AvatarCharacter;
}

void UGGFPA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 캐릭터 최대 걷기 속도 증가
    if(ACharacter* AvatarCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
    {
        UCharacterMovementComponent* CharacterMovement = AvatarCharacter->GetCharacterMovement();
        DefaultMaxWalkSpeed = CharacterMovement->MaxWalkSpeed;
        CharacterMovement->MaxWalkSpeed = DefaultMaxWalkSpeed * MoveSpeedRatio;
    }
}

void UGGFPA_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    // 캐릭터 최대 걷기 속도 복원
    if(ACharacter* AvatarCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
    {
        UCharacterMovementComponent* CharacterMovement = AvatarCharacter->GetCharacterMovement();
        CharacterMovement->MaxWalkSpeed = DefaultMaxWalkSpeed;
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
