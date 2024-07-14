// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFAttributesWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UGGFAttributesWidget::SetActor(AActor* NewActor)
{
    Super::SetActor(NewActor);

    // 기존 시스템 이벤트 언바인딩
    if(TargetSystem.IsValid())
    {
        UnBindAttributeValueChangeEvents();
    }

    // 시스템 교체
    TargetSystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(NewActor);

    // 새로운 시스템 이벤트 바인딩
    if(TargetSystem.IsValid())
    {
        RefreshAttributeValues();
        BindAttributeValueChangeEvents();
    }
}

void UGGFAttributesWidget::RefreshAttributeValues()
{
    {
        bool bFound;
        float NewAttributeValue = TargetSystem->GetGameplayAttributeValue(Attribute, bFound);   \
        if(bFound)
        {
            auto OldAttributeValue = AttributeValue;
            AttributeValue = NewAttributeValue;
            OnAttributeValueChange(OldAttributeValue);
        }
    }

    {
        bool bFound;
        float NewMaxAttributeValue = TargetSystem->GetGameplayAttributeValue(MaxAttribute, bFound);   \
        if(bFound)
        {
            auto OldMaxAttributeValue = MaxAttributeValue;
            MaxAttributeValue = NewMaxAttributeValue;
            OnMaxAttributeValueChange(OldMaxAttributeValue);
        }
    }

    {
        bool bFound;
        float NewAttributeRegenRateValue = TargetSystem->GetGameplayAttributeValue(AttributeRegenRate, bFound);   \
        if(bFound)
        {
            auto OldAttributeRegenRateValue = AttributeRegenRateValue;
            AttributeRegenRateValue = NewAttributeRegenRateValue;
            OnAttributeRegenRateValueChange(OldAttributeRegenRateValue);
        }
    }
}

void UGGFAttributesWidget::BindAttributeValueChangeEvents()
{
    OnAttributeValueChangeHandle = TargetSystem->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ThisClass::OnAttributeChange);
    OnMaxAttributeValueChangeHandle = TargetSystem->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &ThisClass::OnMaxAttributeChange);
    OnAttributeRegenRateValueChangeHandle = TargetSystem->GetGameplayAttributeValueChangeDelegate(AttributeRegenRate).AddUObject(this, &ThisClass::OnAttributeRegenRateChange);
}

void UGGFAttributesWidget::UnBindAttributeValueChangeEvents()
{
    TargetSystem->GetGameplayAttributeValueChangeDelegate(Attribute).Remove(OnAttributeValueChangeHandle);
    TargetSystem->GetGameplayAttributeValueChangeDelegate(MaxAttribute).Remove(OnMaxAttributeValueChangeHandle);
    TargetSystem->GetGameplayAttributeValueChangeDelegate(AttributeRegenRate).Remove(OnAttributeRegenRateValueChangeHandle);
}

void UGGFAttributesWidget::OnAttributeChange(const FOnAttributeChangeData& Data)
{
    AttributeValue = Data.NewValue;
    OnAttributeValueChange(Data.OldValue);
}

void UGGFAttributesWidget::OnMaxAttributeChange(const FOnAttributeChangeData& Data)
{
    MaxAttributeValue = Data.NewValue;
    OnMaxAttributeValueChange(Data.OldValue);
}

void UGGFAttributesWidget::OnAttributeRegenRateChange(const FOnAttributeChangeData& Data)
{
    AttributeRegenRateValue = Data.NewValue;
    OnAttributeRegenRateValueChange(Data.OldValue);
}

void UGGFAttributesWidget::OnAttributeValueChange_Implementation(float OldAttributeValue)
{

}

void UGGFAttributesWidget::OnMaxAttributeValueChange_Implementation(float OldMaxAttributeValue)
{

}

void UGGFAttributesWidget::OnAttributeRegenRateValueChange_Implementation(float OldAttributeRegenRateValue)
{

}
