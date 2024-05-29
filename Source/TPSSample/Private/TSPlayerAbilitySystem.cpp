// Fill out your copyright notice in the Description page of Project Settings.

#include "TSPlayerAbilitySystem.h"

#include "GE_TSCharacterAttributes.h"
#include "GE_TSCharacterStats.h"
#include "Attributes/GEHealthAttributes.h"
#include "Attributes/GEShieldAttributes.h"
#include "Stats/GEAttackSpeedStats.h"
#include "Stats/GEAttackStats.h"
#include "Stats/GEDefenseStats.h"
#include "Stats/GEMoveSpeedStats.h"

UTSPlayerAbilitySystem::UTSPlayerAbilitySystem()
{
    /* Attributes */
    Attributes.AddUnique(UGEHealthAttributes::StaticClass()); // 체력
    Attributes.AddUnique(UGEShieldAttributes::StaticClass()); // 방어막

    /* Stats */
    Stats.AddUnique(UGEAttackStats::StaticClass()); // 공격력
    Stats.AddUnique(UGEDefenseStats::StaticClass()); // 방어력
    Stats.AddUnique(UGEAttackSpeedStats::StaticClass()); // 공격속도
    Stats.AddUnique(UGEMoveSpeedStats::StaticClass()); // 이동속도

    /* Effects */
    Effects.AddUnique(UGE_TSCharacterAttributes::StaticClass()); // 캐릭터 기본 특성 초기화
    Effects.AddUnique(UGE_TSCharacterStats::StaticClass()); // 캐릭터 기본 스탯 초기화
}
