// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GGFCrosshairWidget.h"

#include "Components/Image.h"

void UGGFCrosshairWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    RefreshImage(CenterCrosshairImage);
    RefreshImage(TopCrosshairImage);
    RefreshImage(BottomCrosshairImage);
    RefreshImage(RightCrosshairImage);
    RefreshImage(LeftCrosshairImage);
}

void UGGFCrosshairWidget::RefreshImage(UImage* TargetImage)
{
    if(!TargetImage->GetBrush().GetResourceObject())
    {
        TargetImage->SetBrushTintColor(FLinearColor(1, 1, 1, 0));
    }
    else
    {
        TargetImage->SetBrushTintColor(FLinearColor(1, 1, 1, 1));
    }
}
