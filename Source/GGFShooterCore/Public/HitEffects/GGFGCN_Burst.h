// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Burst.h"
#include "GGFHitEffectDefinition.h"
#include "GGFGCN_Burst.generated.h"

// TODO 폭발물처럼 스폰 장소와 HitResult가 관계없는 경우 처리
/*
 * GCN_Burst에 GGFHitEffectDefinition를 추가한 클래스입니다.
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFGCN_Burst : public UGameplayCueNotify_Burst
{
    GENERATED_BODY()

protected:
    // HitEffectMap에 등록되지 않은 경우 사용할 기본 피격 효과입니다.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    FGGFHitEffectConfig DefaultHitEffect;

    // 피지컬 머터리얼에 따라 피격 효과를 다르게 적용하기 위한 설정입니다.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TMap<TObjectPtr<UPhysicalMaterial>, FGGFHitEffectConfig> HitEffectMap;

protected:
    /* GameplayCueNotify_Static */
    virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

    // 피격 정보에 따라 적절한 피격 효과를 스폰합니다.
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SpawnHitEffect(const FHitResult& HitResult) const;
};
