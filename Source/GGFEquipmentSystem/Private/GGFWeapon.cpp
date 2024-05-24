// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFWeapon.h"

#include "AbilitySystemComponent.h"
#include "GGFEquipmentGameplayTags.h"
#include "Interfaces/GGFCharacterAnimationInterface.h"

AGGFWeapon::AGGFWeapon()
    : bOwnerCharacterValid(false)
{
    EquipmentType = GGFGameplayTags::Equipment::Weapon::Root;
}

void AGGFWeapon::PlayCharacterMontage(UAnimMontage* MontageToPlay)
{
    // OwnerCharacter 유효성 검사
    if(!bOwnerCharacterValid) return;

    // 캐릭터 애니메이션 재생
    IGGFCharacterAnimationInterface::Execute_PlayMontage(Owner, MontageToPlay);
}

void AGGFWeapon::OnEquip_Implementation()
{
    Super::OnEquip_Implementation();

    // OwnerCharacter 유효성 검사
    bOwnerCharacterValid = Owner->Implements<UGGFCharacterAnimationInterface>();
}

void AGGFWeapon::OnUnEquip_Implementation()
{
    Super::OnUnEquip_Implementation();

    // OwnerCharacter 유효성 초기화
    bOwnerCharacterValid = false;
}
