// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/HitEffect/GGFGCN_Burst.h"

#include "Weapon/HitEffect/GGFHitEffect.h"

bool UGGFGCN_Burst::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
    if(const FHitResult* HitResultPtr = Parameters.EffectContext.GetHitResult())
        SpawnHitEffect(*HitResultPtr);

    return Super::OnExecute_Implementation(MyTarget, Parameters);
}

void UGGFGCN_Burst::SpawnHitEffect_Implementation(const FHitResult& HitResult) const
{
    // HitResult 유효성 검사
    if(!HitResult.bBlockingHit) return;

    // HitResult 분석
    UPhysicalMaterial* PhysMaterial = HitResult.PhysMaterial.Get();

    // 적용할 이펙트 선택
    const auto& HitEffectConfig = HitEffectMap.Contains(PhysMaterial) ? HitEffectMap[PhysMaterial] : DefaultHitEffect;

    // 이펙트 적용
    for (const auto& HitEffect : HitEffectConfig.HitEffects)
    {
        // null 검사
        if(HitEffect == nullptr) continue;

        // 이펙트 적용
        HitEffect->SpawnHitEffect(HitResult);
    }
}
