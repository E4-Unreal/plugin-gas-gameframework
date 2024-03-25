// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Projectile/GGFBullet.h"

#include "FunctionLibraries/GGFFunctionLibrary.h"
#include "Weapon/HitEffect/GGFHitEffectDefinition.h"

AGGFBullet::AGGFBullet()
{

}

void AGGFBullet::OnHit_Implementation(const FHitResult& HitResult)
{
    // 데미지 적용
    UGGFFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetInstigator(), HitResult.GetActor());
}

void AGGFBullet::OnMulticastHit_Implementation(const FHitResult& HitResult)
{
    // 피격 효과 스폰
    if(HitEffect)
        HitEffect->SpawnHitEffect(HitResult);

    // 총알 파괴
    Destroy();
}
