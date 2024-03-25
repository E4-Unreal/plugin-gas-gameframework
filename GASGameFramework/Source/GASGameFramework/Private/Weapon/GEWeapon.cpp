// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GGFWeapon.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Character/Interface/GGFCharacterMeshInterface.h"
#include "FunctionLibraries/GGFFunctionLibrary.h"
#include "Weapon/Interface/GGFWeaponAbilityInterface.h"

void AGGFWeapon::OnSelected_Implementation()
{
    GiveAbilities();
}

void AGGFWeapon::OnDeselected_Implementation()
{
    ClearAbilities();
}

void AGGFWeapon::GiveAbilities()
{
    // 유효성 검사
    if(!OwnerAbilitySystem.IsValid()) return;

    // 무기 어빌리티 부여
    AbilitySpecHandles = UGGFFunctionLibrary::GiveAbilitiesToSystem(WeaponAbilities, OwnerAbilitySystem.Get());

    // 부여된 무기 어빌리티에 무기 레퍼런스 추가
    for (const auto& AbilitySpecHandle : AbilitySpecHandles)
    {
        // 유효성 검사
        FGameplayAbilitySpec* AbilitySpec = OwnerAbilitySystem->FindAbilitySpecFromHandle(AbilitySpecHandle);
        if(AbilitySpec == nullptr || AbilitySpec->Ability == nullptr) continue;

        // 인스턴싱 정책 확인
        if(AbilitySpec->Ability->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::InstancedPerActor) continue;

        // 단일 어빌리티 인스턴스 가져오기
        const TArray<UGameplayAbility*>& AbilityInstances = AbilitySpec->GetAbilityInstances();
        UGameplayAbility* AbilityInstance = AbilityInstances[0];

        // 무기 레퍼런스 주입
        if(!AbilityInstance->GetClass()->ImplementsInterface(UGGFWeaponAbilityInterface::StaticClass())) continue;
        IGGFWeaponAbilityInterface::Execute_SetWeapon(AbilityInstance, this);

        // ShowDebug AbilitySystem에서 확인하기 위해 CDO를 어빌리티 인스턴스로 교체
        AbilitySpec->Ability = AbilityInstance;
    }
}

void AGGFWeapon::ClearAbilities()
{
    // 유효성 검사
    if(!OwnerAbilitySystem.IsValid()) return;

    // 무기 어빌리티 제거
    for (const auto& AbilitySpecHandle : AbilitySpecHandles)
    {
        OwnerAbilitySystem->ClearAbility(AbilitySpecHandle);
    }
}

void AGGFWeapon::OnEquip_Implementation()
{
    Super::OnEquip_Implementation();

    // AbilitySystem 캐싱
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);

    // 캐릭터 메시 캐싱
    if(Owner->GetClass()->ImplementsInterface(UGGFCharacterMeshInterface::StaticClass()))
    {
        ThirdPersonMesh = IGGFCharacterMeshInterface::Execute_GetThirdPersonFullBodyMesh(Owner);
        FirstPersonMesh = IGGFCharacterMeshInterface::Execute_GetFirstPersonArmsMesh(Owner);
    }
}

void AGGFWeapon::OnUnEquip_Implementation()
{
    Super::OnUnEquip_Implementation();

    // AbilitySystem 캐시 제거
    OwnerAbilitySystem = nullptr;

    // 캐릭터 메시 캐싱 제거
    ThirdPersonMesh = nullptr;
    FirstPersonMesh = nullptr;
}
