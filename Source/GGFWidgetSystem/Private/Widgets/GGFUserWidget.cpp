// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFUserWidget.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

void UGGFUserWidget::SetTargetActor(AActor* NewTargetActor)
{
    TargetActor = NewTargetActor;
    SetTargetSystem(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor.Get()));
}

void UGGFUserWidget::SetTargetSystem(UAbilitySystemComponent* NewTargetSystem)
{
    TargetSystem = NewTargetSystem;
}
