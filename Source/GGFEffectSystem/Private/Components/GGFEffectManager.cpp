// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFEffectManager.h"

#include "Effects/GGFEffectDefinition.h"

void UGGFEffectManager::PlayEffectsAtActor(AActor* Actor, bool bAttach)
{
    if(auto Definition = EffectDefinitionContainer.GetEffectDefinition())
    {
        Definition->PlayEffectsAtActor(Actor, bAttach);
    }
}

void UGGFEffectManager::PlayEffectsAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName)
{
    if(auto Definition = EffectDefinitionContainer.GetEffectDefinition())
    {
        Definition->PlayEffectsAtSocket(ComponentToAttach, SocketName);
    }
}

void UGGFEffectManager::PlayEffectsByHitResult(const FHitResult& HitResult, bool bAttach)
{
    if(auto Definition = EffectDefinitionContainer.GetEffectDefinition())
    {
        Definition->PlayEffectsByHitResult(HitResult, bAttach);
    }
}
