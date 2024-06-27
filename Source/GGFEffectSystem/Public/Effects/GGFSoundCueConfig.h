// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFEffectConfig.h"
#include "GGFSoundCueConfig.generated.h"

class USoundCue;

/**
 * 사운드 큐 데이터
 */
USTRUCT(BlueprintType)
struct FGGFSoundCueData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USoundCue> SoundCue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VolumeMultiplier = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PitchMultiplier = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartTime = 0;
};

/**
 * 사운드 큐 전용 데이터 에셋
 */
UCLASS()
class GGFEFFECTSYSTEM_API UGGFSoundCueConfig : public UGGFEffectConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintGetter = GetSoundCueData)
    FGGFSoundCueData SoundCueData;

public:
    /* EffectConfig */

    virtual void PlayEffectAtActor(AActor* Actor, bool bAttach) override;
    virtual void PlayEffectAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName) override;
    virtual void PlayEffectByHitResult(const FHitResult& HitResult, bool bAttach) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void Init(const FGGFSoundCueData& NewSoundCueData) { SoundCueData = NewSoundCueData; }

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGGFSoundCueData& GetSoundCueData() const { return SoundCueData; }
};
