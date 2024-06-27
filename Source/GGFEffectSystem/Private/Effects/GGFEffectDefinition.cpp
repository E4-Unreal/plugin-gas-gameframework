// Fill out your copyright notice in the Description page of Project Settings.

#include "Effects/GGFEffectDefinition.h"

#include "Effects/GGFEffectConfig.h"

void UGGFEffectDefinition::PlayEffectsAtActor(AActor* Actor, bool bAttach)
{
    for (auto EffectConfig : EffectConfigs)
    {
        if(EffectConfig) EffectConfig->PlayEffectAtActor(Actor, bAttach);
    }
}

void UGGFEffectDefinition::PlayEffectsAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName)
{
    for (auto EffectConfig : EffectConfigs)
    {
        if(EffectConfig) EffectConfig->PlayEffectAtSocket(ComponentToAttach, SocketName);
    }
}

void UGGFEffectDefinition::PlayEffectsByHitResult(const FHitResult& HitResult, bool bAttach)
{
    for (auto EffectConfig : EffectConfigs)
    {
        if(EffectConfig) EffectConfig->PlayEffectByHitResult(HitResult, bAttach);
    }
}
