// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotifyTypes.h"
#include "GEGameplayCueNotifyTypes.generated.h"

/**
 * FGameplayCueNotify_CascadeInfo
 *
 * 캐스케이드 파티클 시스템 정보
 *
 * UE5.3 기준으로 FGameplayCueNotify_SpawnContext는 USTRUCT가 아니기 때문에
 * FGameplayCueNotify_SpawnCondition와 FGameplayCueNotify_PlacementInfo 사용 시
 * LNK2019 오류가 발생하기 때문에 FGameplayCueParameters로 대체하였습니다.
 */
USTRUCT(BlueprintType)
struct FGameplayCueNotify_CascadeInfo
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)
    TObjectPtr<UParticleSystem> ParticleSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)
    FVector Scale = FVector::OneVector;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)
    uint32 bCastShadow : 1;

public:
    bool PlayParticleEffect(AActor* Target, const FGameplayCueParameters& Parameters) const;

    void ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;
};
