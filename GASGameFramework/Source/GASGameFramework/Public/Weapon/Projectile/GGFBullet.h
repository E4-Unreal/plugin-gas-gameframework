// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFProjectile.h"
#include "GGFBullet.generated.h"

/*
 * 충돌 즉시 피격 이벤트 핸들링되는 총알 클래스
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API AGGFBullet : public AGGFProjectile
{
    GENERATED_BODY()

public:
    AGGFBullet();

protected:
    virtual void OnHit_Implementation(const FHitResult& HitResult) override;
    virtual void OnMulticastHit_Implementation(const FHitResult& HitResult) override;
};
