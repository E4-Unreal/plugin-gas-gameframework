// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GGFPlayerAbilitySystem.h"

#include "Abilities/GGFGA_Interact.h"
#include "Abilities/GGFGA_Sprint.h"

UGGFPlayerAbilitySystem::UGGFPlayerAbilitySystem()
{
    /* 기본 어빌리티 설정 */
    Abilities.AddUnique(UGGFGA_Interact::StaticClass()); // 상호작용
    Abilities.AddUnique(UGGFGA_Sprint::StaticClass()); // 빠르게 달리기
}
