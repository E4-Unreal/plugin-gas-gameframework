// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFWidgetComponent.h"

#include "Widgets/GGFActorWidget.h"
#include "Widgets/GGFUserWidget.h"

UGGFWidgetComponent::UGGFWidgetComponent()
{
    Space = EWidgetSpace::Screen;
    bDrawAtDesiredSize = true;
}

void UGGFWidgetComponent::InitWidget()
{
    Super::InitWidget();

    if(auto CastedWidget = Cast<UGGFActorWidget>(GetWidget()))
    {
        CastedWidget->SetActor(GetOwner());
    }
}
