// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFActorComponent.h"
#include "GGFEffectManager.generated.h"

class UGGFEffectDefinition;

/**
 * 기존 데이터 에셋 혹은 데이터 에셋 인스턴스를 선택하여 사용할 수 있는 구조체
 */
USTRUCT(BlueprintType)
struct FGGFEffectDefinitionContainer
{
    GENERATED_BODY()

    // true 설정 시 기존 데이터 에셋 대신 데이터 에셋 인스턴스 사용
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseInstance = false;

    // 기존 데이터 에셋
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditConditionHides, EditCondition = "!bUseInstance"))
    TObjectPtr<UGGFEffectDefinition> EffectDefinition;

    // 데이터 에셋 인스턴스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta = (EditConditionHides, EditCondition = "bUseInstance"))
    TObjectPtr<UGGFEffectDefinition> InstancedEffectDefinition;

    FORCEINLINE UGGFEffectDefinition* GetEffectDefinition() const { return bUseInstance ? InstancedEffectDefinition : EffectDefinition; }
};

class UGGFEffectDefinition;

UCLASS(meta=(BlueprintSpawnableComponent))
class GGFEFFECTSYSTEM_API UGGFEffectManager : public UGGFActorComponent
{
    GENERATED_BODY()

public:
    // 이펙트가 정의된 데이터 에셋 컨테이너
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGGFEffectDefinitionContainer EffectDefinitionContainer;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsAtActor(AActor* Actor, bool bAttach = false);

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsAtSocket(UPrimitiveComponent* ComponentToAttach, FName SocketName = NAME_None);

    UFUNCTION(BlueprintCallable)
    virtual void PlayEffectsByHitResult(const FHitResult& HitResult, bool bAttach = false);
};
