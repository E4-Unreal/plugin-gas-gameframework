// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEProjectile.h"
#include "GEBullet.generated.h"

/*
 * 충돌 즉시 피격 이벤트 핸들링되는 총알 클래스
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API AGEBullet : public AGEProjectile
{
    GENERATED_BODY()

public:
    AGEBullet();

protected:
    virtual void OnHit_Implementation(const FHitResult& HitResult) override;
    virtual void OnMulticastHit_Implementation(const FHitResult& HitResult) override;
};
