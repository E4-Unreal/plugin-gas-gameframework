// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFAttributesBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UGGFAttributesBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    RefreshAttributeBar(InDeltaTime);
}

void UGGFAttributesBar::OnAttributeValueChange_Implementation(float OldAttributeValue)
{
    if(AttributeValueText == nullptr) return;

    AttributeValueText->SetText(FText::FromString(FString::FromInt(AttributeValue)));
}

void UGGFAttributesBar::OnMaxAttributeValueChange_Implementation(float OldMaxAttributeValue)
{
    if(MaxAttributeValueText == nullptr) return;

    MaxAttributeValueText->SetText(FText::FromString(FString::FromInt(MaxAttributeValue)));
}

void UGGFAttributesBar::OnAttributeRegenRateValueChange_Implementation(float OldAttributeRegenRateValue)
{
    if(AttributeRegenRateValueText == nullptr) return;

    FString AttributeRegenRateValueString = AttributeRegenRateValue >= 0 ? "+" : "-";
    AttributeRegenRateValueString += FString::FromInt(AttributeRegenRateValue);
    AttributeRegenRateValueText->SetText(FText::FromString(AttributeRegenRateValueString));
}

void UGGFAttributesBar::RefreshAttributeBar(float InDeltaTime)
{
    if(AttributeBar == nullptr) return;

    AttributeBar->SetPercent(FMath::FInterpTo(AttributeBar->GetPercent(), AttributeValue / MaxAttributeValue, InDeltaTime, InterpSpeed));
}
