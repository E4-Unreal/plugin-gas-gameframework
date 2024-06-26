// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GGFCharacterAbility.h"

#include "GameFramework/Character.h"

void UGGFCharacterAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    AvatarCharacter = CastChecked<ACharacter>(ActorInfo->AvatarActor);
}
