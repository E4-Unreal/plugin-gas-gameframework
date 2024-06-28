// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFProjectile.h"
#include "GGFSpawnableProjectile.generated.h"

/**
 * 충돌 위치에 특정 액터를 스폰하는 발사체 클래스입니다.
 */
UCLASS()
class GGFSHOOTERCORE_API AGGFSpawnableProjectile : public AGGFProjectile
{
    GENERATED_BODY()

protected:
    // 스폰 대상
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<AActor> ActorToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseHitResult;

    // 스폰 대상 수명 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float LifeSpan = 10;

protected:
    /* Projectile */

    virtual void OnSphereColliderHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
