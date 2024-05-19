// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFFireArmAbility.h"

#include "Weapons/GGFFireArm.h"

bool UGGFFireArmAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                            const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) && FireArm.IsValid();
}

void UGGFFireArmAbility::OnRep_Weapon()
{
    Super::OnRep_Weapon();

    // 총기 레퍼런스 캐싱
    AActor* CachedWeapon = GetWeapon();
    FireArm = CachedWeapon == nullptr ? nullptr : Cast<AGGFFireArm>(CachedWeapon);
}
