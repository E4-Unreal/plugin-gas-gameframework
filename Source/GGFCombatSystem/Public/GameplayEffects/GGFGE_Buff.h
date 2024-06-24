// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GGFGE_Buff.generated.h"

/**
 * 일정 시간동안 특정 스탯을 올려주는 버프 전용 게임플레이 이펙트 클래스입니다.
 */
UCLASS()
class GGFCOMBATSYSTEM_API UGGFGE_Buff : public UGameplayEffect
{
    GENERATED_BODY()

protected:
    FGameplayModifierInfo* AttackModifierPtr;
    FGameplayModifierInfo* DefenseModifierPtr;
    FGameplayModifierInfo* AttackSpeedModifierPtr;
    FGameplayModifierInfo* MoveSpeedModifierPtr;
    FGameplayModifierInfo* AbilityHasteModifierPtr;

public:
    UGGFGE_Buff();

    /* API */

    UFUNCTION(BlueprintCallable)
    void SetAttackModifier(EGameplayModOp::Type ModifierOp = EGameplayModOp::Multiplicitive, float Magnitude = 1.5);

    UFUNCTION(BlueprintCallable)
    void SetDefenseModifier(EGameplayModOp::Type ModifierOp = EGameplayModOp::Multiplicitive, float Magnitude = 1.5);

    UFUNCTION(BlueprintCallable)
    void SetAttackSpeedModifier(EGameplayModOp::Type ModifierOp = EGameplayModOp::Multiplicitive, float Magnitude = 1.5);

    UFUNCTION(BlueprintCallable)
    void SetMoveSpeedModifier(EGameplayModOp::Type ModifierOp = EGameplayModOp::Multiplicitive, float Magnitude = 1.5);

    UFUNCTION(BlueprintCallable)
    void SetAbilityHasteModifier(EGameplayModOp::Type ModifierOp = EGameplayModOp::Multiplicitive, float Magnitude = 1.5);

protected:
    void SetModifier(FGameplayAttribute Attribute, FGameplayModifierInfo*& ModifierPtr, EGameplayModOp::Type ModifierOp, float Magnitude);
};
