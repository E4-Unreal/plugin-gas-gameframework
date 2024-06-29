// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFHealthWidget.h"

#include "AbilitySystemComponent.h"
#include "Attributes/GGFHealthAttributes.h"
#include "Attributes/GGFShieldAttributes.h"

UGGFHealthWidget::UGGFHealthWidget()
{
    Attribute = UGGFHealthAttributes::GetHealthAttribute();
    MaxAttribute = UGGFHealthAttributes::GetMaxHealthAttribute();
    AttributeRegenRate = UGGFHealthAttributes::GetHealthRegenRateAttribute();
    ShieldAttribute = UGGFShieldAttributes::GetShieldAttribute();
}

void UGGFHealthWidget::RefreshAttributeValues()
{
    Super::RefreshAttributeValues();

    {
        bool bFound;
        float NewAttributeValue = TargetSystem->GetGameplayAttributeValue(ShieldAttribute, bFound);   \
        if(bFound)
        {
            auto OldShieldAttributeValue = ShieldAttributeValue;
            ShieldAttributeValue = NewAttributeValue;
            OnShieldAttributeValueChange(OldShieldAttributeValue);
        }
    }
}

void UGGFHealthWidget::BindAttributeValueChangeEvents()
{
    Super::BindAttributeValueChangeEvents();

    OnShieldAttributeValueChangeHandle = TargetSystem->GetGameplayAttributeValueChangeDelegate(ShieldAttribute).AddUObject(this, &ThisClass::OnShieldAttributeChange);
}

void UGGFHealthWidget::UnBindAttributeValueChangeEvents()
{
    Super::UnBindAttributeValueChangeEvents();

    TargetSystem->GetGameplayAttributeValueChangeDelegate(ShieldAttribute).Remove(OnShieldAttributeValueChangeHandle);
}

void UGGFHealthWidget::OnShieldAttributeChange(const FOnAttributeChangeData& Data)
{
    ShieldAttributeValue = Data.NewValue;
    OnShieldAttributeValueChange(Data.OldValue);
}

void UGGFHealthWidget::OnShieldAttributeValueChange_Implementation(float OldAttributeValue)
{
}
