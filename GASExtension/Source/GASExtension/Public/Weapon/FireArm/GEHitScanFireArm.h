// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEFireArm.h"
#include "GEHitScanFireArm.generated.h"

class UGEHitEffectDefinition;
class UGameplayEffect;

UCLASS()
class GASEXTENSION_API AGEHitScanFireArm : public AGEFireArm
{
    GENERATED_BODY()

    // 피격 대상에게 적용할 GE 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|HitScan", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

    // 라인 트레이스의 최대 거리입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|HitScan", meta = (AllowPrivateAccess = true))
    float MaxDistance = 100000.f;

    // 피격 효과
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|HitScan", meta = (AllowPrivateAccess = true))
    UGEHitEffectDefinition* HitEffect;

#if WITH_EDITORONLY_DATA
  // 디버그를 위한 라인 트레이스 시각화 기능 활성화
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|HitScan", meta = (AllowPrivateAccess = true))
    bool bEnableDebugLine;
#endif

protected:
    virtual void OnFire_Implementation() override;

    UFUNCTION(BlueprintNativeEvent)
    void OnHit(const FHitResult& HitResult);

    UFUNCTION(NetMulticast, Reliable)
    void OnMulticastHit(const FHitResult& HitResult);
};
