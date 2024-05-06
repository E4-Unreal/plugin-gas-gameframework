// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/GEAttributeSetBase.h"

#include "AbilitySystemComponent.h"

void UGEAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // Clamp Current Value
    ClampAttributes(Attribute, NewValue);
}

void UGEAttributeSetBase::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::PreAttributeBaseChange(Attribute, NewValue);

    // Clamp Base Value
    ClampAttributes(Attribute, NewValue);
}

void UGEAttributeSetBase::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    // MaxAttribute 값 변경 시 Attribute / MaxAttribute 비율 유지
    AdjustAttributes(Attribute, OldValue, NewValue);
}

void UGEAttributeSetBase::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute,
                                                      const FGameplayAttributeData& MaxAttribute, const float OldMaxValue, const float NewMaxValue,
                                                      const FGameplayAttribute& AffectedAttributeProperty) const
{
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    if (!FMath::IsNearlyEqual(OldMaxValue, NewMaxValue) && AbilityComp)
    {
        // Attribute / MaxAttribute 비율이 유지되도록 Attribute 값 변경
        const float CurrentValue = AffectedAttribute.GetCurrentValue();
        const float NewDelta = (OldMaxValue > 0.f) ? (CurrentValue * NewMaxValue / OldMaxValue) - CurrentValue : NewMaxValue;

        AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
    }
}

void UGEAttributeSetBase::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
}

void UGEAttributeSetBase::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}
