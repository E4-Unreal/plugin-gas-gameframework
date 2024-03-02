// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectApplier.generated.h"

class UGameplayEffect;

/*
 * 대상 액터에게 GameplayEffects를 적용할 수 있도록 도와주는 간단한 액터 컴포넌트입니다.
 * 총알이나 불처럼 충돌 이벤트에 ApplyEffectsToTarget 메서드를 바인딩하여 사용하면 됩니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGameplayEffectApplier : public UActorComponent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

public:
    UFUNCTION(BlueprintCallable, Category = "GameplayEffectApplier")
    void ApplyEffectsToTarget(AActor* Target);
};
