// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFHealthBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UGGFHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    RefreshAttributeBar(InDeltaTime);
}

void UGGFHealthBar::OnAttributeValueChange_Implementation(float OldAttributeValue)
{
    if(HealthValueText == nullptr) return;

    HealthValueText->SetText(FText::FromString(FString::FromInt(AttributeValue)));
}

void UGGFHealthBar::OnMaxAttributeValueChange_Implementation(float OldMaxAttributeValue)
{
    if(MaxHealthValueText == nullptr) return;

    MaxHealthValueText->SetText(FText::FromString(FString::FromInt(MaxAttributeValue)));
}

void UGGFHealthBar::OnAttributeRegenRateValueChange_Implementation(float OldAttributeRegenRateValue)
{
    if(HealthRegenRateValueText == nullptr) return;

    FString AttributeRegenRateValueString = AttributeRegenRateValue >= 0 ? "+" : "-";
    AttributeRegenRateValueString += FString::FromInt(AttributeRegenRateValue);
    HealthRegenRateValueText->SetText(FText::FromString(AttributeRegenRateValueString));
}

void UGGFHealthBar::OnShieldAttributeValueChange_Implementation(float OldAttributeValue)
{
    if(ShieldValueText == nullptr) return;

    FString ShieldValueString = "+";
    ShieldValueString += FString::FromInt(ShieldAttributeValue);
    ShieldValueText->SetText(FText::FromString(ShieldValueString));
}

void UGGFHealthBar::RefreshAttributeBar(float InDeltaTime)
{
    if(HealthBar == nullptr || ShieldBar == nullptr) return;

    /*
     * 1. Health + Shield <= MaxHealth
     * - Health: CurrentHealth / MaxHealth
     * - Shield: (CurrentHealth + CurrentShield) / MaxHealth
     *
     * 2. Health + Shield > MaxHealth
     * - Health: CurrentHealth / (MaxHealth + CurrentShield)
     * - Shield: 1
     */

    // 방어막 >= 최대 체력
    if(AttributeValue + ShieldAttributeValue <= MaxAttributeValue) // 체력 + 방어막 <= 최대 체력
    {
        HealthBar->SetPercent(FMath::FInterpTo(HealthBar->GetPercent(), AttributeValue / MaxAttributeValue, InDeltaTime, InterpSpeed));
        ShieldBar->SetPercent(FMath::FInterpTo(ShieldBar->GetPercent(), (AttributeValue + ShieldAttributeValue) / MaxAttributeValue, InDeltaTime, InterpSpeed));
    }
    else // 체력 + 방어막 > 최대 체력
    {
        HealthBar->SetPercent(FMath::FInterpTo(HealthBar->GetPercent(), AttributeValue / (MaxAttributeValue + ShieldAttributeValue), InDeltaTime, InterpSpeed));
        ShieldBar->SetPercent(FMath::FInterpTo(ShieldBar->GetPercent(), 1, InDeltaTime, InterpSpeed));
    }
}
