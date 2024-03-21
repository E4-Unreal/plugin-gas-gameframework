// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Projectile/GEBullet.h"

#include "FunctionLibraries/GEFunctionLibrary.h"
#include "Weapon/HitEffect/GEHitEffectDefinition.h"

AGEBullet::AGEBullet()
{

}

void AGEBullet::OnHit_Implementation(const FHitResult& HitResult)
{
    // 데미지 적용
    UGEFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetInstigator(), HitResult.GetActor());
}

void AGEBullet::OnMulticastHit_Implementation(const FHitResult& HitResult)
{
    // 피격 효과 스폰
    if(HitEffect)
        HitEffect->SpawnHitEffect(HitResult);

    // 총알 파괴
    Destroy();
}
