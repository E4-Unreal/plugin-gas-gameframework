// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEFireArm.h"
#include "GEProjectileFireArm.generated.h"

class AGEProjectile;

/*
 * 발사체 스폰 방식의 총기 클래스입니다.
 * 데미지(EffectsToApply)나 피격 효과(HitEffect)는 Projectile 클래스에서 설정합니다.
 */
UCLASS()
class GASEXTENSION_API AGEProjectileFireArm : public AGEFireArm
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<AGEProjectile> ProjectileClass;

protected:
    virtual void OnFire_Implementation() override;
};
