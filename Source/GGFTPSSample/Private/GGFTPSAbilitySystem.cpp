// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFTPSAbilitySystem.h"

#include "Attributes/GEHealthAttributes.h"
#include "Attributes/GEShieldAttributes.h"
#include "Stats/GEAttackSpeedStats.h"
#include "Stats/GEAttackStats.h"
#include "Stats/GEDefenseStats.h"
#include "Stats/GEMoveSpeedStats.h"

UGGFTPSAbilitySystem::UGGFTPSAbilitySystem()
{
    /* Attributes */
    DefaultAttributes.Add(UGEHealthAttributes::StaticClass()); // 체력
    DefaultAttributes.Add(UGEShieldAttributes::StaticClass()); // 방어막

    /* Stats */
    DefaultStats.Add(UGEAttackStats::StaticClass()); // 공격력
    DefaultStats.Add(UGEDefenseStats::StaticClass()); // 방어력
    DefaultStats.Add(UGEAttackSpeedStats::StaticClass()); // 공격속도
    DefaultStats.Add(UGEMoveSpeedStats::StaticClass()); // 이동속도
}
