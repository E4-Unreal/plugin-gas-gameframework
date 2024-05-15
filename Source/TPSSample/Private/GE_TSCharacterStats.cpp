// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_TSCharacterStats.h"

#include "Stats/GEAttackSpeedStats.h"
#include "Stats/GEAttackStats.h"
#include "Stats/GEDefenseStats.h"
#include "Stats/GEMoveSpeedStats.h"

UGE_TSCharacterStats::UGE_TSCharacterStats()
{
    /* Modifiers 설정 */
    // 공격력
    const float MaxAttack = 999;
    const FGameplayModifierInfo MaxAttackModifier
    {
        UGEAttackStats::GetMaxAttackAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxAttack))
    };

    const float Attack = 20;
    const FGameplayModifierInfo AttackModifier
    {
        UGEAttackStats::GetAttackAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(Attack))
    };

    // 방어력
    const float MaxDefense = 999;
    const FGameplayModifierInfo MaxDefenseModifier
    {
        UGEDefenseStats::GetMaxDefenseAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxDefense))
    };

    const float Defense = 10;
    const FGameplayModifierInfo DefenseModifier
    {
        UGEDefenseStats::GetDefenseAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(Defense))
    };

    // 공격 속도
    const float MaxAttackSpeed = 10;
    const FGameplayModifierInfo MaxAttackSpeedModifier
    {
        UGEAttackSpeedStats::GetMaxAttackSpeedAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxAttackSpeed))
    };

    const float AttackSpeed = 1;
    const FGameplayModifierInfo AttackSpeedModifier
    {
        UGEAttackSpeedStats::GetAttackSpeedAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(AttackSpeed))
    };

    // 이동 속도
    const float MaxMoveSpeed = 10;
    const FGameplayModifierInfo MaxMoveSpeedModifier
    {
        UGEMoveSpeedStats::GetMaxMoveSpeedAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MaxMoveSpeed))
    };

    const float MoveSpeed = 10;
    const FGameplayModifierInfo MoveSpeedModifier
    {
        UGEMoveSpeedStats::GetMoveSpeedAttribute(),
        EGameplayModOp::Override,
        FGameplayEffectModifierMagnitude(FScalableFloat(MoveSpeed))
    };

    /* Modifiers 추가 */
    // 공격력
    Modifiers.Add(MaxAttackModifier);
    Modifiers.Add(AttackModifier);

    // 방어력
    Modifiers.Add(MaxDefenseModifier);
    Modifiers.Add(DefenseModifier);

    // 공격 속도
    Modifiers.Add(MaxAttackSpeedModifier);
    Modifiers.Add(AttackSpeedModifier);

    // 이동 속도
    Modifiers.Add(MaxMoveSpeedModifier);
    Modifiers.Add(MoveSpeedModifier);

    /* 기타 옵션 설정 */
    DurationPolicy = EGameplayEffectDurationType::Instant;
}
