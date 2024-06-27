// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFEffectConfig.h"
#include "GGFParticleConfig.generated.h"

USTRUCT(BlueprintType)
struct FGGFParticleData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UParticleSystem> ParticleSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPreserveRatio))
    FVector Scale = FVector::One();
};

struct FFXSystemSpawnParameters;

/**
 * 파티클 시스템 전용 데이터 에셋
 */
UCLASS()
class GGFEFFECTSYSTEM_API UGGFParticleConfig : public UGGFEffectConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintGetter = GetParticleData)
    FGGFParticleData ParticleData;

public:
    /* EffectConfig */

    virtual void PlayEffectAtActor(AActor* Actor, bool bAttach) override;
    virtual void PlayEffectAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName) override;
    virtual void PlayEffectByHitResult(const FHitResult& HitResult, bool bAttach) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void Init(const FGGFParticleData& NewParticleData) { ParticleData = NewParticleData; }

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGGFParticleData& GetParticleData() const { return ParticleData; }

protected:
    /* 메서드 */

    virtual void SpawnEmitterAtLocationWithParams(const FFXSystemSpawnParameters& SpawnParams);

    virtual void SpawnEmitterAttachedWithParams(const FFXSystemSpawnParameters& SpawnParams);
};
