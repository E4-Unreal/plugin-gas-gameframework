// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GGFPlayerAbilitySystem.h"

#include "Abilities/GGFPA_Interact.h"
#include "Abilities/GGFPA_Sprint.h"

UGGFPlayerAbilitySystem::UGGFPlayerAbilitySystem()
{
    /* 기본 어빌리티 설정 */
    DefaultAbilities.AddUnique(UGGFPA_Interact::StaticClass()); // 상호작용
    DefaultAbilities.AddUnique(UGGFPA_Sprint::StaticClass()); // 빠르게 달리기
}
