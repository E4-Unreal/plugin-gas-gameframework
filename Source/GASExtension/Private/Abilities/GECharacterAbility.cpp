// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GECharacterAbility.h"

#include "GameFramework/Character.h"

void UGECharacterAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    AvatarCharacter = CastChecked<ACharacter>(ActorInfo->AvatarActor);
}
