// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GGFPlayerAbilitySystem.h"

#include "Abilities/GGFGA_Interact.h"

UGGFPlayerAbilitySystem::UGGFPlayerAbilitySystem()
{
    /* 기본 어빌리티 설정 */
    DefaultAbilities.AddUnique(UGGFGA_Interact::StaticClass()); // 상호작용
}
