// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFWeapon.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GEBlueprintFunctionLibrary.h"
#include "GGFEquipmentGameplayTags.h"
#include "Interfaces/GGFCharacterInterface.h"
#include "Interfaces/GGFWeaponAbilityInterface.h"

AGGFWeapon::AGGFWeapon()
{
    EquipmentType = GGFGameplayTags::Equipment::Weapon::Root;
}

void AGGFWeapon::GiveAbilities()
{
    // 유효성 검사
    if(!OwnerAbilitySystem.IsValid()) return;

    // 무기 어빌리티 부여
    AbilitySpecHandles = UGEBlueprintFunctionLibrary::GiveAbilitiesToSystem(WeaponAbilities, OwnerAbilitySystem.Get());

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

void AGGFWeapon::PlayCharacterMontage(UAnimMontage* MontageToPlay)
{
    // OwnerCharacter 유효성 검사
    if(!bOwnerCharacterValid) return;

    // 캐릭터 애니메이션 재생
    IGGFCharacterInterface::Execute_PlayMontage(Owner, MontageToPlay);
}

void AGGFWeapon::OnEquip_Implementation()
{
    Super::OnEquip_Implementation();

    // AbilitySystem 캐싱
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);

    // OwnerCharacter 유효성 검사
    bOwnerCharacterValid = Owner->Implements<UGGFCharacterInterface>();
}

void AGGFWeapon::OnUnEquip_Implementation()
{
    Super::OnUnEquip_Implementation();

    // AbilitySystem 캐시 제거
    OwnerAbilitySystem = nullptr;

    // OwnerCharacter 유효성 초기화
    bOwnerCharacterValid = false;
}

void AGGFWeapon::Activate_Implementation()
{
    GiveAbilities();
}

void AGGFWeapon::Deactivate_Implementation()
{
    ClearAbilities();
}
