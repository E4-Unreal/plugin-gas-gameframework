// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GGFInteractionInfoWidget.h"

#include "Components/TextBlock.h"

void UGGFInteractionInfoWidget::SetDisplayName_Implementation(const FText& NewDisplayName)
{
    DisplayNameText->SetText(NewDisplayName);
}

void UGGFInteractionInfoWidget::SetInteractionInfo_Implementation(const FText& NewInteractionInfo)
{
    InteractionInfoText->SetText(NewInteractionInfo);
}
