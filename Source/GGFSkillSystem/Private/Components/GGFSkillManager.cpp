// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFSkillManager.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/GEGameplayAbility.h"
#include "Data/GGFSkillDataSubsystem.h"
#include "Data/GGFSkillDefinition.h"

void UGGFSkillManager::Reset()
{
    Super::Reset();

    for (auto& Slot : Slots)
    {
        ClearSkillSlot(Slot);
    }
}

void UGGFSkillManager::BeginPlay()
{
    Super::BeginPlay();

    // 기본 설정 적용
    for (const auto& Slot : Slots)
    {
        if(Slot.ID >= 0)
            SetSkillSlotByID(Slot.InputTag, Slot.ID);
        else if(Slot.Definition)
            SetSkillSlotByDefinition(Slot.InputTag, Slot.Definition);
    }
}

void UGGFSkillManager::SetSkillSlotByID(const FGameplayTag& InputTag, int32 ID)
{
    // 입력 유효성 검사
    if(!InputTag.IsValid() || ID < 0) return;

    // 존재하는 슬롯인지 확인
    if(!Slots.Contains(InputTag)) return;

    // ID 설정
    auto& Slot = *Slots.FindByKey(InputTag);
    Slot.ID = ID;

    // 슬롯 설정
    SetSkillSlotByDefinition(InputTag, GetSkillDefinition(ID));
}

void UGGFSkillManager::SetSkillSlotByDefinition(const FGameplayTag& InputTag, UGGFSkillDefinition* Definition)
{
    // 입력 유효성 검사
    if(!InputTag.IsValid() || Definition == nullptr) return;

    // 존재하는 슬롯인지 확인
    if(!Slots.Contains(InputTag)) return;
    auto& Slot = *Slots.FindByKey(InputTag);

    // 슬롯 초기화
    ClearSkillSlot(Slot);

    // 데이터 에셋 설정
    Slot.Definition = Definition;

    if(auto OwnerSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
    {
        // 스킬 어빌리티 부여
        const auto& SkillData = Definition->GetData();
        auto AbilitySpec = OwnerSystem->BuildAbilitySpecFromClass(SkillData.AbilityClass);
        Slot.AbilitySpecHandle = OwnerSystem->GiveAbility(AbilitySpec);

        // 어빌리티 인스턴스 설정
        if(auto ActivatableAbilitySpec = OwnerSystem->FindAbilitySpecFromHandle(Slot.AbilitySpecHandle))
        {
            if(auto AbilityInstance = Cast<UGEGameplayAbility>(ActivatableAbilitySpec->GetPrimaryInstance()))
            {
                // 입력 ID 설정
                ActivatableAbilitySpec->InputID = GetTypeHash(InputTag);

                // 쿨타임 설정
                AbilityInstance->CooldownTime = SkillData.CoolTime;
                AbilityInstance->CooldownTag = Slot.CooldownTag;
                AbilityInstance->CreateCooldownEffectInstance();
            }
        }
    }
}

UGGFSkillDefinition* UGGFSkillManager::GetSkillDefinition(int32 ID) const
{
    if(auto DataSubsystem = GetSkillDataSubsystem())
    {
        return DataSubsystem->GetDefinition(ID);
    }

    return nullptr;
}

UGGFSkillDataSubsystem* UGGFSkillManager::GetSkillDataSubsystem() const
{
    if(auto GameInstance = GetOwner()->GetGameInstance())
    {
        return GameInstance->GetSubsystem<UGGFSkillDataSubsystem>();
    }

    return nullptr;
}

void UGGFSkillManager::ClearSkillSlot(FGGFSkillSlot& Slot)
{
    // 중복 호출 방지
    if(Slot.IsEmpty()) return;

    // 부여된 스킬 제거
    if(auto OwnerSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
    {
        OwnerSystem->ClearAbility(Slot.AbilitySpecHandle);
    }

    // 슬롯 초기화
    Slot.Clear();
}
