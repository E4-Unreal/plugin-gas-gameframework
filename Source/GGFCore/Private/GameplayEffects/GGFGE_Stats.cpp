// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFGE_Stats.h"

#include "GGFGameplayTags.h"
#include "Stats/GGFAttackStats.h"
#include "Stats/GGFAbilityHasteStats.h"
#include "Stats/GGFAttackSpeedStats.h"
#include "Stats/GGFDefenseStats.h"
#include "Stats/GGFMoveSpeedStats.h"

UGGFGE_Stats::UGGFGE_Stats()
{
    SET_STAT_MODIFIER(UGGFAttackStats, Attack);
    SET_STAT_MODIFIER(UGGFDefenseStats, Defense);
    SET_STAT_MODIFIER(UGGFMoveSpeedStats, MoveSpeed);
    SET_STAT_MODIFIER(UGGFAttackSpeedStats, AttackSpeed);
    SET_STAT_MODIFIER(UGGFAbilityHasteStats, AbilityHaste);
}
