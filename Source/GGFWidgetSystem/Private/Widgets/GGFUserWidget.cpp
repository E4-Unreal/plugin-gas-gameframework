// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFUserWidget.h"

#include "Logging.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Blueprint/WidgetTree.h"

void UGGFUserWidget::Refresh_Implementation()
{
#if WITH_EDITOR
    LOG_WIDGET_DETAIL(Log, TEXT(""))
#endif
}

void UGGFUserWidget::SetTargetActor(AActor* NewTargetActor)
{
    TargetActor = NewTargetActor;
    SetTargetSystem(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor.Get()));

#if WITH_EDITOR
    LOG_WIDGET_DETAIL(Log, TEXT("%s"), *NewTargetActor->GetName())
#endif
}

void UGGFUserWidget::SetTargetSystem(UAbilitySystemComponent* NewTargetSystem)
{
    TargetSystem = NewTargetSystem;
}
