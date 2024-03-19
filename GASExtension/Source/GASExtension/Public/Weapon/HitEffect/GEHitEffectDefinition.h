// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GEHitEffectDefinition.generated.h"

class UGEHitEffect;

USTRUCT(Atomic, BlueprintType)
struct FGSFHitEffectConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UGEHitEffect*> HitEffects;
};

/*
 * 히트 스캔 방식의 총기나 근접 무기 등에서는 무기 자체에서 피격 판정이 이루어지기 때문에 직접 피격 효과를 스폰해야 하지만,
 * 총알처럼 발사체를 사용하는 경우에는 발사체에서 피격 효과를 스폰해야 합니다.
 *
 * 이처럼 서로 다른 클래스에서 동일한 방식으로 피격 효과를 스폰하기 위한 데이터 에셋입니다.
 */
UCLASS(BlueprintType)
class GASEXTENSION_API UGEHitEffectDefinition : public UDataAsset
{
	GENERATED_BODY()

    // HitEffectMap에 등록되지 않은 경우 사용할 기본 피격 효과입니다.
	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FGSFHitEffectConfig DefaultHitEffect;

	// 피지컬 머터리얼에 따라 피격 효과를 다르게 적용하기 위한 설정입니다.
    UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
    TMap<TObjectPtr<UPhysicalMaterial>, FGSFHitEffectConfig> HitEffectMap;

public:
    // 피격 정보에 따라 적절한 피격 효과를 스폰합니다.
	UFUNCTION(BlueprintCallable)
	void SpawnHitEffect(const FHitResult& HitResult);
};
