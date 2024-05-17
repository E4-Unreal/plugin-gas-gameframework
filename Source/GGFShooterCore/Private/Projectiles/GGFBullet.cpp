// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/GGFBullet.h"

#include "GEBlueprintFunctionLibrary.h"

AGGFBullet::AGGFBullet()
{

}

void AGGFBullet::OnHit_Implementation(const FHitResult& HitResult)
{
    // 데미지 적용
    UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetInstigator(), HitResult.GetActor());
}

void AGGFBullet::OnMulticastHit_Implementation(const FHitResult& HitResult)
{
    // 피격 효과 스폰
    HandleGameplayCueNotify(HitResult);

    // 총알 파괴
    Destroy();
}
