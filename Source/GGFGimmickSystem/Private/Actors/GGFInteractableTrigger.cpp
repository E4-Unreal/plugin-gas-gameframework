// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableTrigger.h"

#include "Components/GGFActivatableComponent.h"
#include "Components/GGFTriggerComponent.h"

AGGFInteractableTrigger::AGGFInteractableTrigger()
{
    /* Trigger Component */
    TriggerComponent = CreateDefaultSubobject<UGGFTriggerComponent>(TEXT("TriggerComponent"));

    /* Activatable Component */
    ActivatableComponent = CreateDefaultSubobject<UGGFActivatableComponent>(TEXT("ActivatableComponent"));
}

void AGGFInteractableTrigger::OnPawnInteract_Implementation(APawn* OtherPawn)
{
    GetTriggerComponent()->ToggleTargets(OtherPawn);
}

bool AGGFInteractableTrigger::TryActivate_Implementation(AActor* InCauser, AActor* InInstigator)
{
    return GetActivatableComponent()->TryActivate(InCauser, InInstigator);
}

bool AGGFInteractableTrigger::TryDeactivate_Implementation(AActor* InCauser, AActor* InInstigator)
{
    return GetActivatableComponent()->TryDeactivate(InCauser, InInstigator);
}
