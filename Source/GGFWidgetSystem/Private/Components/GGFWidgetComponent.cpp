// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFWidgetComponent.h"

#include "Widgets/GGFUserWidget.h"

void UGGFWidgetComponent::SetWidget(UUserWidget* InWidget)
{
    Super::SetWidget(InWidget);

    if(auto CastedWidget = Cast<UGGFUserWidget>(InWidget))
    {
        CastedWidget->SetTargetActor(GetOwner());
    }
}
