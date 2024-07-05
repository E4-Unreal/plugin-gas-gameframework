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
    ActivatableComponent->SetupAttachment(GetDisplayMesh());
}

void AGGFInteractableTrigger::OnPawnInteract_Implementation(APawn* OtherPawn)
{
    GetTriggerComponent()->ToggleTargets();
}

bool AGGFInteractableTrigger::Activate_Implementation(AActor* InstigatorActor)
{
    return GetActivatableComponent()->TryActivate(this);
}

bool AGGFInteractableTrigger::Deactivate_Implementation(AActor* InstigatorActor)
{
    return GetActivatableComponent()->TryDeactivate(this);
}
