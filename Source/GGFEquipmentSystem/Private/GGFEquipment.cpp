// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFEquipment.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayEffect.h"
#include "GEBlueprintFunctionLibrary.h"
#include "GGFEquipmentGameplayTags.h"
#include "Interfaces/GGFWeaponAbilityInterface.h"

AGGFEquipment::AGGFEquipment()
{
    /* 초기화 */

    // 리플리케이트 설정
    SetReplicates(true);

    // 기본값 설정
    using namespace GGFGameplayTags::Equipment;
    EquipmentType = Root;
    EquipmentSlot = Slot::Root;
}

void AGGFEquipment::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 메모리 할당
    PassiveEffectSpecHandles.Reserve(PassiveEffects.Num());
    PassiveAbilitySpecHandles.Reserve(PassiveAbilities.Num());
    ActiveAbilitySpecHandles.Reserve(ActiveAbilities.Num());
}

void AGGFEquipment::SetOwner(AActor* NewOwner)
{
    // 기존 소유자로부터 장비 장착 해제
    if(AActor* OldOwner = GetOwner())
    {
        // 장비 비활성화
        Execute_Deactivate(this);

        // 장비 장착 해제
        OnUnEquip();

        // 레퍼런스 제거
        OwnerAbilitySystem = nullptr;
    }

    // 소유자 변경
    Super::SetOwner(NewOwner);

    // 새로운 소유자에게 장비 장착
    if(NewOwner)
    {
        // 레퍼런스 할당
        OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(NewOwner);

        // 장비 장착
        OnEquip();
    }
}

void AGGFEquipment::OnRep_Owner()
{
    Super::OnRep_Owner();

    // 레퍼런스 할당
    OwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
}

void AGGFEquipment::Equip_Implementation(AActor* NewOwner)
{
    SetOwner(NewOwner);
}

void AGGFEquipment::UnEquip_Implementation()
{
    SetOwner(nullptr);
}

void AGGFEquipment::Activate_Implementation()
{
    // 액티브 게임플레이 이펙트 적용
    ApplyEffectsToOwner(ActiveEffects, ActiveEffectSpecHandles);

    // 액티브 어빌리티 부여
    GiveAbilitiesToOwner(ActiveAbilities, ActiveAbilitySpecHandles);
}

void AGGFEquipment::Deactivate_Implementation()
{
    // 액티브 게임플레이 이펙트 제거
    RemoveEffectsFromOwner(ActiveEffectSpecHandles);

    // 액티브 어빌리티 제거
    ClearAbilitiesFromOwner(ActiveAbilitySpecHandles);
}

void AGGFEquipment::OnEquip_Implementation()
{
    // 패시브 게임플레이 이펙트 적용
    ApplyEffectsToOwner(PassiveEffects, PassiveEffectSpecHandles);

    // 패시브 어빌리티 부여
    GiveAbilitiesToOwner(PassiveAbilities, PassiveAbilitySpecHandles);
}

void AGGFEquipment::OnUnEquip_Implementation()
{
    // 패시브 게임플레이 이펙트 제거
    RemoveEffectsFromOwner(PassiveEffectSpecHandles);

    // 패시브 어빌리티 제거
    ClearAbilitiesFromOwner(PassiveAbilitySpecHandles);
}

void AGGFEquipment::GiveAbilitiesToOwner(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGive,
    TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles)
{
    // 유효성 검사
    if(!GetOwnerAbilitySystem()) return;

    // AbilitySpecHandles 초기화
    if(!AbilitySpecHandles.IsEmpty()) AbilitySpecHandles.Reset();

    // 어빌리티 부여
    AbilitySpecHandles = UGEBlueprintFunctionLibrary::GiveAbilitiesToSystem(AbilitiesToGive, GetOwnerAbilitySystem());

    // 부여된 무기 어빌리티에 무기 레퍼런스 추가
    for (const auto& AbilitySpecHandle : AbilitySpecHandles)
    {
        // 유효성 검사
        FGameplayAbilitySpec* AbilitySpec = GetOwnerAbilitySystem()->FindAbilitySpecFromHandle(AbilitySpecHandle);
        if(AbilitySpec == nullptr || AbilitySpec->Ability == nullptr) continue;

        // 인스턴싱 정책 확인
        if(AbilitySpec->Ability->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::InstancedPerActor) continue;

        // 단일 어빌리티 인스턴스 가져오기
        const TArray<UGameplayAbility*>& AbilityInstances = AbilitySpec->GetAbilityInstances();
        UGameplayAbility* AbilityInstance = AbilityInstances[0];

        // ShowDebug AbilitySystem에서 확인하기 위해 CDO를 어빌리티 인스턴스로 교체
        AbilitySpec->Ability = AbilityInstance;

        // TODO 장비 어빌리티 인터페이스로 변경
        // 무기 레퍼런스 주입
        if(!AbilityInstance->GetClass()->ImplementsInterface(UGGFWeaponAbilityInterface::StaticClass())) continue;
        IGGFWeaponAbilityInterface::Execute_SetWeapon(AbilityInstance, this);
    }
}

void AGGFEquipment::ClearAbilitiesFromOwner(TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles)
{
    // 유효성 검사
    if(!GetOwnerAbilitySystem()) return;

    // 어빌리티 제거
    for (const auto& AbilitySpecHandle : AbilitySpecHandles)
    {
        GetOwnerAbilitySystem()->ClearAbility(AbilitySpecHandle);
    }

    // AbilitySpecHandles 초기화
    AbilitySpecHandles.Reset();
}

void AGGFEquipment::ApplyEffectsToOwner(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply,
    TArray<FActiveGameplayEffectHandle>& EffectSpecHandles)
{
    // 유효성 검사
    if(!GetOwnerAbilitySystem()) return;

    // EffectSpecHandles 초기화
    if(!EffectSpecHandles.IsEmpty()) EffectSpecHandles.Reset();

    // 게임플레이 이펙트 적용
    EffectSpecHandles = UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(EffectsToApply, GetOwnerAbilitySystem());
}

void AGGFEquipment::RemoveEffectsFromOwner(TArray<FActiveGameplayEffectHandle>& EffectSpecHandles)
{
    // 유효성 검사
    if(!GetOwnerAbilitySystem()) return;

    // 게임플레이 이펙트 제거
    for (const auto& EffectSpecHandle : EffectSpecHandles)
    {
        GetOwnerAbilitySystem()->RemoveActiveGameplayEffect(EffectSpecHandle);
    }

    // EffectSpecHandles 초기화
    EffectSpecHandles.Reset();
}
