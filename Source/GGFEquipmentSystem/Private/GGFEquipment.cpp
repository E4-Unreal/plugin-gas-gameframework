// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFEquipment.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayEffect.h"
#include "GGFBlueprintFunctionLibrary.h"
#include "Components/GGFEquipmentDataManager.h"
#include "Data/GGFEquipmentDefinition.h"

FName AGGFEquipment::SkeletalMeshName(TEXT("SkeletalMesh"));
FName AGGFEquipment::DataManagerName(TEXT("DataManager"));

AGGFEquipment::AGGFEquipment(const FObjectInitializer& ObjectInitializer)
{
    /* 초기화 */

    // 리플리케이트 설정
    bReplicates = true;

    /* SkeletalMesh */
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SetRootComponent(SkeletalMesh);

    /* DataManager */
    DataManager = CreateDefaultSubobject<UGGFEquipmentDataManager>(DataManagerName);
}

void AGGFEquipment::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // 초기화
    OnIDUpdated(GetDataManager()->GetID());
}

void AGGFEquipment::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    // DataManager 이벤트 바인딩
    GetDataManager()->OnIDUpdated.AddDynamic(this, &ThisClass::OnIDUpdated);
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

/* Equipment Interface */

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
    // 장비 스탯 적용
    GetDataManager()->ApplyStatsEffectToTarget(GetOwner());

    // 액티브 게임플레이 이펙트 적용
    ApplyEffectsToOwner(ActiveEffects, ActiveEffectSpecHandles);

    // 액티브 어빌리티 부여
    GiveAbilitiesToOwner(ActiveAbilities, ActiveAbilitySpecHandles);
}

void AGGFEquipment::Deactivate_Implementation()
{
    // 장비 스탯 제거
    GetDataManager()->RemoveStatsEffectFromTarget(GetOwner());

    // 액티브 게임플레이 이펙트 제거
    RemoveEffectsFromOwner(ActiveEffectSpecHandles);

    // 액티브 어빌리티 제거
    ClearAbilitiesFromOwner(ActiveAbilitySpecHandles);
}

const FGameplayTag AGGFEquipment::GetEquipmentSlot_Implementation() const
{
    return GetDataManager()->GetEquipmentData().EquipmentSlot;
}

const FGameplayTag AGGFEquipment::GetEquipmentType_Implementation() const
{
    return GetDataManager()->GetEquipmentData().EquipmentType;
}

/* Data Interface */

int32 AGGFEquipment::GetID_Implementation()
{
    return GetDataManager()->GetID();
}

void AGGFEquipment::SetID_Implementation(int32 NewID)
{
    GetDataManager()->SetID(NewID);
}

const FGGFEquipmentData& AGGFEquipment::GetEquipmentData() const
{
    return GetDataManager()->GetEquipmentData();
}

void AGGFEquipment::OnIDUpdated(int32 NewID)
{
    // 장비 설정
    const auto& EquipmentData = GetDataManager()->GetEquipmentData();
    GetSkeletalMesh()->SetSkeletalMesh(EquipmentData.SkeletalMesh);
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
    AbilitySpecHandles = UGGFBlueprintFunctionLibrary::GiveAbilitiesToSystem(AbilitiesToGive, GetOwnerAbilitySystem());
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
    EffectSpecHandles = UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(this, EffectsToApply);
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
