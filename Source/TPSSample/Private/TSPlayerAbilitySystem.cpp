// Fill out your copyright notice in the Description page of Project Settings.

#include "TSPlayerAbilitySystem.h"

#include "GE_TSCharacterAttributes.h"
#include "GE_TSCharacterStats.h"
#include "Attributes/GGFHealthAttributes.h"
#include "Attributes/GGFShieldAttributes.h"
#include "Stats/GGFAttackSpeedStats.h"
#include "Stats/GGFAttackStats.h"
#include "Stats/GGFDefenseStats.h"
#include "Stats/GGFMoveSpeedStats.h"

UTSPlayerAbilitySystem::UTSPlayerAbilitySystem()
{
    /* Attributes */
    Attributes.AddUnique(UGGFHealthAttributes::StaticClass()); // 체력
    Attributes.AddUnique(UGGFShieldAttributes::StaticClass()); // 방어막

    /* Stats */
    Stats.AddUnique(UGGFAttackStats::StaticClass()); // 공격력
    Stats.AddUnique(UGGFDefenseStats::StaticClass()); // 방어력
    Stats.AddUnique(UGGFAttackSpeedStats::StaticClass()); // 공격속도
    Stats.AddUnique(UGGFMoveSpeedStats::StaticClass()); // 이동속도

    /* Effects */
    Effects.AddUnique(UGE_TSCharacterAttributes::StaticClass()); // 캐릭터 기본 특성 초기화
    Effects.AddUnique(UGE_TSCharacterStats::StaticClass()); // 캐릭터 기본 스탯 초기화
}
