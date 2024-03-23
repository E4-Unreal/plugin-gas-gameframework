// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GEWeapon.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Character/Interface/GECharacterMeshInterface.h"
#include "FunctionLibraries/GEFunctionLibrary.h"

void AGEWeapon::OnSelected_Implementation()
{
    GiveAbilities();
}

void AGEWeapon::OnDeselected_Implementation()
{
    ClearAbilities();
}

void AGEWeapon::GiveAbilities()
{
    // 유효성 검사
    if(!OwnerAbilitySystem.IsValid()) return;

    // 무기 어빌리티 부여
    AbilitySpecHandles = UGEFunctionLibrary::GiveAbilitiesToSystem(WeaponAbilities, OwnerAbilitySystem.Get());
}

void AGEWeapon::ClearAbilities()
{
    // 유효성 검사
    if(!OwnerAbilitySystem.IsValid()) return;

    // 무기 어빌리티 제거
    for (const auto& AbilitySpecHandle : AbilitySpecHandles)
    {
        OwnerAbilitySystem->ClearAbility(AbilitySpecHandle);
    }
}

void AGEWeapon::OnEquip_Implementation()
{
    Super::OnEquip_Implementation();

    // AbilitySystem 캐싱
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);

    // 캐릭터 메시 캐싱
    if(Owner->GetClass()->ImplementsInterface(UGECharacterMeshInterface::StaticClass()))
    {
        ThirdPersonMesh = IGECharacterMeshInterface::Execute_GetThirdPersonFullBodyMesh(Owner);
        FirstPersonMesh = IGECharacterMeshInterface::Execute_GetFirstPersonArmsMesh(Owner);
    }
}

void AGEWeapon::OnUnEquip_Implementation()
{
    Super::OnUnEquip_Implementation();

    // AbilitySystem 캐시 제거
    OwnerAbilitySystem = nullptr;

    // 캐릭터 메시 캐싱 제거
    ThirdPersonMesh = nullptr;
    FirstPersonMesh = nullptr;
}
