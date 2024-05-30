// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayCues/GEGameplayCueNotify_Burst.h"

UGEGameplayCueNotify_Burst::UGEGameplayCueNotify_Burst()
{

}

bool UGEGameplayCueNotify_Burst::OnExecute_Implementation(AActor* MyTarget,
    const FGameplayCueParameters& Parameters) const
{
    for (const auto& CascadeParticle : CascadeParticles)
    {
        CascadeParticle.PlayParticleEffect(MyTarget, Parameters);
    }

    return Super::OnExecute_Implementation(MyTarget, Parameters);
}
