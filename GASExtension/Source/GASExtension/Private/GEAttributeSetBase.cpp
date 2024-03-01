// Fill out your copyright notice in the Description page of Project Settings.

#include "GEAttributeSetBase.h"

#include "AbilitySystemComponent.h"

void UGEAttributeSetBase::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
    const FGameplayAttributeData& MaxAttribute, const float NewMaxValue,
    const FGameplayAttribute& AffectedAttributeProperty) const
{
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
    if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
    {
        // Attribute / MaxAttribute 비율이 유지되도록 Attribute 값 변경
        const float CurrentValue = AffectedAttribute.GetCurrentValue();
        const float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

        AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
    }
}
