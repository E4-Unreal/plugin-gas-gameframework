// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFHealArea.h"

#include "Components/GGFEffectAreaComponent.h"
#include "GameplayEffects/GGFGE_ContinuousHeal.h"

AGGFHealArea::AGGFHealArea()
{
    GetEffectAreaComponent()->EffectsToApply.Emplace(UGGFGE_ContinuousHeal::StaticClass());
}
