// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GGFGameplayEffect.generated.h"

class UTargetTagsGameplayEffectComponent;
class UTargetTagRequirementsGameplayEffectComponent;

/**
 * GASGameFramework 플러그인 전용 게임플레이 이펙트 클래스
 */
UCLASS()
class GGFCORE_API UGGFGameplayEffect : public UGameplayEffect
{
    GENERATED_BODY()

    /* 컴포넌트 */

    TWeakObjectPtr<UTargetTagRequirementsGameplayEffectComponent> TargetTagRequirementsComponent;
    TWeakObjectPtr<UTargetTagsGameplayEffectComponent> TargetTagsGameplayEffectComponent;

public:
    UGGFGameplayEffect();

    /* API */

    UFUNCTION(BlueprintCallable)
    UTargetTagRequirementsGameplayEffectComponent* GetOrFindTargetTagRequirementsComponent();

    UFUNCTION(BlueprintCallable)
    UTargetTagsGameplayEffectComponent* GetOrFindTargetTagsGameplayEffectComponent();

protected:
    template<class T>
    TWeakObjectPtr<T> GetOrFindComponent(TWeakObjectPtr<T>& Component) const;
};
