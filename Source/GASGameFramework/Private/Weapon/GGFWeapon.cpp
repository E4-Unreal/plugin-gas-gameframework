// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GGFWeapon.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Character/Interface/GGFCharacterInterface.h"
#include "GEBlueprintFunctionLibrary.h"
#include "Weapon/Abilities/GGFWeaponAbilityInterface.h"

AGGFWeapon::AGGFWeapon()
{
    EquipmentType = GGFGameplayTags::Equipment::Weapon::Weapon;
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

void AGGFWeapon::PlayFirstPersonMontage(UAnimMontage* Montage) const
{
    if(FirstPersonAnimInstance.IsValid() && Montage)
        FirstPersonAnimInstance->Montage_Play(Montage);
}

void AGGFWeapon::PlayThirdPersonMontage(UAnimMontage* Montage) const
{
    if(ThirdPersonAnimInstance.IsValid() && Montage)
        ThirdPersonAnimInstance->Montage_Play(Montage);
}

void AGGFWeapon::LinkAnimClasses() const
{
    LinkCharacterAnimClasses(FirstPersonAnimInstance, FirstPersonAnimLinkClasses);
    LinkCharacterAnimClasses(ThirdPersonAnimInstance, ThirdPersonAnimLinkClasses);
}

void AGGFWeapon::UnLinkAnimClasses() const
{
    UnlinkCharacterAnimClasses(FirstPersonAnimInstance, FirstPersonAnimLinkClasses);
    UnlinkCharacterAnimClasses(ThirdPersonAnimInstance, ThirdPersonAnimLinkClasses);
}

void AGGFWeapon::OnEquip_Implementation()
{
    Super::OnEquip_Implementation();

    // AbilitySystem 캐싱
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);

    // 캐릭터 메시 캐싱
    if(Owner->Implements<UGGFCharacterInterface>())
    {
        const USkeletalMeshComponent* ThirdPersonMesh = IGGFCharacterInterface::Execute_GetThirdPersonMesh(Owner);
        ThirdPersonAnimInstance = ThirdPersonMesh ? ThirdPersonMesh->GetAnimInstance() : nullptr;

        const USkeletalMeshComponent* FirstPersonMesh = IGGFCharacterInterface::Execute_GetFirstPersonMesh(Owner);
        FirstPersonAnimInstance = FirstPersonMesh ? FirstPersonMesh->GetAnimInstance() : nullptr;
    }
}

void AGGFWeapon::OnUnEquip_Implementation()
{
    Super::OnUnEquip_Implementation();

    // AbilitySystem 캐시 제거
    OwnerAbilitySystem = nullptr;

    // 캐릭터 메시 캐싱 제거
    ThirdPersonAnimInstance = nullptr;
    FirstPersonAnimInstance = nullptr;
}

void AGGFWeapon::LinkCharacterAnimClasses(TWeakObjectPtr<UAnimInstance> AnimInstance,
    const TArray<TSubclassOf<UAnimInstance>>& AnimLinkClasses)
{
    if(AnimInstance.IsValid())
    {
        for (TSubclassOf<UAnimInstance> AnimLinkClass : AnimLinkClasses)
        {
            // 유효성 검사
            if(AnimLinkClass == nullptr) continue;

            // 애님 클래스 링크
            AnimInstance->LinkAnimClassLayers(AnimLinkClass);
        }
    }
}

void AGGFWeapon::UnlinkCharacterAnimClasses(TWeakObjectPtr<UAnimInstance> AnimInstance,
    const TArray<TSubclassOf<UAnimInstance>>& AnimLinkClasses)
{
    if(AnimInstance.IsValid())
    {
        for (TSubclassOf<UAnimInstance> AnimLinkClass : AnimLinkClasses)
        {
            // 유효성 검사
            if(AnimLinkClass == nullptr) continue;

            // 애님 클래스 링크
            AnimInstance->UnlinkAnimClassLayers(AnimLinkClass);
        }
    }
}

void AGGFWeapon::Activate_Implementation()
{
    GiveAbilities();
    LinkAnimClasses();
}

void AGGFWeapon::Deactivate_Implementation()
{
    ClearAbilities();
    UnLinkAnimClasses();
}
