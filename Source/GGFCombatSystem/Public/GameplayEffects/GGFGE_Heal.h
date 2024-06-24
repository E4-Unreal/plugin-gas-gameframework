// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GGFGameplayEffect.h"
#include "GGFGE_Heal.generated.h"

/**
 * 힐 전용 게임플레이 이펙트로 시전 즉시 일정 수치의 체력을 회복합니다.
 */
UCLASS()
class GGFCOMBATSYSTEM_API UGGFGE_Heal : public UGGFGameplayEffect
{
    GENERATED_BODY()

protected:
    FGameplayModifierInfo* HealthModifierPtr;

public:
    UGGFGE_Heal();

    UFUNCTION(BlueprintCallable)
    void SetHealMagnitude(float NewMagnitude);
};
