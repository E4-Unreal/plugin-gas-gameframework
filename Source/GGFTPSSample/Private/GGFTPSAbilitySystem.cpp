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
    DefaultAttributes.AddUnique(UGEHealthAttributes::StaticClass()); // 체력
    DefaultAttributes.AddUnique(UGEShieldAttributes::StaticClass()); // 방어막

    /* Stats */
    DefaultStats.AddUnique(UGEAttackStats::StaticClass()); // 공격력
    DefaultStats.AddUnique(UGEDefenseStats::StaticClass()); // 방어력
    DefaultStats.AddUnique(UGEAttackSpeedStats::StaticClass()); // 공격속도
    DefaultStats.AddUnique(UGEMoveSpeedStats::StaticClass()); // 이동속도
}
