// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFWidgetComponent.h"

#include "Widgets/GGFUserWidget.h"

UGGFWidgetComponent::UGGFWidgetComponent()
{
    Space = EWidgetSpace::Screen;
    bDrawAtDesiredSize = true;
}

void UGGFWidgetComponent::InitWidget()
{
    Super::InitWidget();

    if(auto CastedWidget = Cast<UGGFUserWidget>(GetWidget()))
    {
        CastedWidget->SetTargetActor(GetOwner());
    }
}
