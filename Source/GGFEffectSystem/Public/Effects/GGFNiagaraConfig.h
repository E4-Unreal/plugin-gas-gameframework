// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFEffectConfig.h"
#include "GGFNiagaraConfig.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FGGFNiagaraData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UNiagaraSystem> NiagaraSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPreserveRatio))
    FVector Scale = FVector::One();
};

/**
 * 나이아가라 시스템 전용 데이터 에셋
 */
UCLASS()
class GGFEFFECTSYSTEM_API UGGFNiagaraConfig : public UGGFEffectConfig
{
    GENERATED_BODY()


protected:
    UPROPERTY(EditAnywhere, BlueprintGetter = GetNiagaraData)
    FGGFNiagaraData NiagaraData;

public:
    /* EffectConfig */

    virtual void PlayEffectAtActor(AActor* Actor, bool bAttach) override;
    virtual void PlayEffectAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName) override;
    virtual void PlayEffectByHitResult(const FHitResult& HitResult, bool bAttach) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void Init(const FGGFNiagaraData& NewNiagaraData) { NiagaraData = NewNiagaraData; }

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGGFNiagaraData& GetNiagaraData() const { return NiagaraData; }
};
