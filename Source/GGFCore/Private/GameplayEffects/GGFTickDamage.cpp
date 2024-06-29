// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayEffects/GGFTickDamage.h"

#include "GGFGameplayTags.h"
#include "Attributes/GGFHealthAttributes.h"
#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GameplayEffects/Calculations/GGFDamageCalculation.h"

UGGFTickDamage::UGGFTickDamage()
{
    /* 태그 설정 */
    auto LocalTargetTagRequirementsComponent = GetOrFindTargetTagRequirementsComponent();
    LocalTargetTagRequirementsComponent->ApplicationTagRequirements.IgnoreTags.AddLeafTag(State::Buff::Invinsible);
    LocalTargetTagRequirementsComponent->OngoingTagRequirements.IgnoreTags.AddLeafTag(State::Buff::Invinsible);

    /* 기본 데미지 계산식 설정 */
    FGameplayEffectExecutionDefinition ExecutionDefinition;
    ExecutionDefinition.CalculationClass = UGGFDamageCalculation::StaticClass();
    Executions.Emplace(ExecutionDefinition);

    // 데미지 모디파이어 추가
    FGameplayModifierInfo DamageModifier;
    DamageModifier.Attribute = UGGFHealthAttributes::GetDamageAttribute();
    DamageModifier.ModifierOp = EGameplayModOp::Additive;
    DamageModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(0);
    int32 Index = Modifiers.Emplace(DamageModifier);
    DamageModifierPtr = &Modifiers[Index];
}
