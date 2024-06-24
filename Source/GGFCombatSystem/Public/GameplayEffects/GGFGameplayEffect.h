// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GGFGameplayEffect.generated.h"

class UTargetTagRequirementsGameplayEffectComponent;

/**
 *
 */
UCLASS()
class GGFCOMBATSYSTEM_API UGGFGameplayEffect : public UGameplayEffect
{
    GENERATED_BODY()

    /* 컴포넌트 */

    TWeakObjectPtr<UTargetTagRequirementsGameplayEffectComponent> TargetTagRequirementsComponent;

public:
    UGGFGameplayEffect();

    /* Getter */

    TWeakObjectPtr<UTargetTagRequirementsGameplayEffectComponent> GetOrFindTargetTagRequirementsComponent();
};
