// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/GGFSkillDefinition.h"

#include "Abilities/GameplayAbility.h"

const FGGFSkillData FGGFSkillData::EmptyData;

bool UGGFSkillDefinition::InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase)
{
    // 구조체 캐스팅
    if(auto NewData = static_cast<FGGFSkillData*>(NewDataTableRowBase))
    {
        // 데이터 설정
        Data = *NewData;
        return true;
    }

    return false;
}

bool UGGFSkillDefinition::IsValid() const
{
    return Super::IsValid() && Data.AbilityClass;
}
