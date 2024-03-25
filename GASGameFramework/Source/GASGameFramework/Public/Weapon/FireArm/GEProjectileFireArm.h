// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFFireArm.h"
#include "GGFProjectileFireArm.generated.h"

class AGGFProjectile;

/*
 * 발사체 스폰 방식의 총기 클래스입니다.
 * 데미지(EffectsToApply)나 피격 효과(HitEffect)는 Projectile 클래스에서 설정합니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API AGGFProjectileFireArm : public AGGFFireArm
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<AGGFProjectile> ProjectileClass;

protected:
    virtual void OnFire_Implementation() override;
};
