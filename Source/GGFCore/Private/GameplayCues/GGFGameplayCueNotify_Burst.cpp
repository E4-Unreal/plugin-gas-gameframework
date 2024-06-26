// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayCues/GGFGameplayCueNotify_Burst.h"

UGGFGameplayCueNotify_Burst::UGGFGameplayCueNotify_Burst()
{

}

bool UGGFGameplayCueNotify_Burst::OnExecute_Implementation(AActor* MyTarget,
    const FGameplayCueParameters& Parameters) const
{
    for (const auto& CascadeParticle : CascadeParticles)
    {
        CascadeParticle.PlayParticleEffect(MyTarget, Parameters);
    }

    return Super::OnExecute_Implementation(MyTarget, Parameters);
}
