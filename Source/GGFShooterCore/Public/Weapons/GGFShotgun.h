// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFProjectileFireArm.h"
#include "GGFShotgun.generated.h"

// TODO 스폰 직후 샷건 총알끼리 오버랩된 경우 충돌이 무시되지 않는 버그 수정 필요
/**
 * 여러 발사체를 동시에 흩뿌리는 샷건 계열 무기입니다.
 * 현재는 별도의 클래스로 분리되어 있지만 부모 클래스에 옵션으로서 통합될 수 있습니다.
 */
UCLASS()
class GGFSHOOTERCORE_API AGGFShotgun : public AGGFProjectileFireArm
{
    GENERATED_BODY()

protected:
    // 발사체 개수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1))
    int32 ProjectileNum = 6;

    // 발사체 분산을 위한 각도 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1, ClampMax = 90))
    int32 ConeHalfAngle = 10;

protected:
    /* FireArm */

    virtual void OnFire_Implementation() override;

    // 발사체 스폰 방향 계산
    UFUNCTION(BlueprintCallable)
    virtual void CalculateProjectileDirections(const FVector& FireDirection, TArray<FVector>& ProjectileDirections) const;
};
