// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GGFEquipmentAbility.h"

#include "Components/GGFEquipmentManager.h"

void UGGFEquipmentAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    EquipmentManager = ActorInfo->AvatarActor->GetComponentByClass<UGGFEquipmentManager>();

    bValid = EquipmentManager.IsValid();
}

bool UGGFEquipmentAbility::InternalCanActivate()
{
    return Super::InternalCanActivate() && GetEquipment();
}
