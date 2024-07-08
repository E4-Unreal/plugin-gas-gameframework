// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFUserWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Blueprint/WidgetTree.h"

void UGGFUserWidget::SetTargetActor(AActor* NewTargetActor)
{
    TargetActor = NewTargetActor;
    SetTargetSystem(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor.Get()));

    // 하위 위젯에도 Target 주입
    TArray<UWidget*> ChildWidgets;
    WidgetTree->GetAllWidgets(ChildWidgets);

    for (auto ChildWidget : ChildWidgets)
    {
        if(auto CastedWidget = Cast<UGGFUserWidget>(ChildWidget)) CastedWidget->SetTargetActor(NewTargetActor);
    }
}

void UGGFUserWidget::SetTargetSystem(UAbilitySystemComponent* NewTargetSystem)
{
    TargetSystem = NewTargetSystem;
}
