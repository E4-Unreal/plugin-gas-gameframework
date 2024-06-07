// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GEPawnAbility.h"

void UGEPawnAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    AvatarPawn = CastChecked<APawn>(ActorInfo->AvatarActor);
}
