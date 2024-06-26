﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GGFEquipmentDefinition.h"

#include "Stats/GEAbilityHasteStats.h"
#include "Stats/GEAttackSpeedStats.h"
#include "Stats/GEAttackStats.h"
#include "Stats/GEDefenseStats.h"
#include "Stats/GEMoveSpeedStats.h"

const FGGFEquipmentData FGGFEquipmentData::EmptyEquipmentData;

UGameplayEffect* UGGFEquipmentDefinition::CreateStatsEffect()
{
    // 빈 게임플레이 이펙트 생성
    UGameplayEffect* NewStats = NewObject<UGameplayEffect>(this, *(Data.DisplayName.ToString() + " Stats"));
    NewStats->DurationPolicy = EGameplayEffectDurationType::Infinite;
    NewStats->Modifiers.Reserve(5);
    if(!FMath::IsNearlyZero(Data.Attack)) NewStats->Modifiers.Emplace(CreateModifier(UGEAttackStats::GetAttackAttribute(), Data.Attack));
    if(!FMath::IsNearlyZero(Data.Defense)) NewStats->Modifiers.Emplace(CreateModifier(UGEDefenseStats::GetDefenseAttribute(), Data.Defense));
    if(!FMath::IsNearlyZero(Data.AttackSpeed)) NewStats->Modifiers.Emplace(CreateModifier(UGEAttackSpeedStats::GetAttackSpeedAttribute(), Data.AttackSpeed));
    if(!FMath::IsNearlyZero(Data.MoveSpeed)) NewStats->Modifiers.Emplace(CreateModifier(UGEMoveSpeedStats::GetMoveSpeedAttribute(), Data.MoveSpeed));
    if(!FMath::IsNearlyZero(Data.AbilityHaste)) NewStats->Modifiers.Emplace(CreateModifier(UGEAbilityHasteStats::GetAbilityHasteAttribute(), Data.AbilityHaste));

    return NewStats;
}

FGameplayModifierInfo UGGFEquipmentDefinition::CreateModifier(const FGameplayAttribute& Attribute, float Value,
    EGameplayModOp::Type ModOp)
{
    return FGameplayModifierInfo
    {
        Attribute,
        ModOp,
        FGameplayEffectModifierMagnitude(FScalableFloat(Value))
    };
}

bool UGGFEquipmentDefinition::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 구조체 캐스팅
    if(auto NewData = static_cast<FGGFEquipmentData*>(NewDataTableRowBase))
    {
        // 데이터 설정
        Data = *NewData;
        Stats = CreateStatsEffect();
        return true;
    }

    return false;
}
