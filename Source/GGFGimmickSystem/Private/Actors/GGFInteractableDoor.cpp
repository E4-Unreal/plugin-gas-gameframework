// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableDoor.h"

#include "Components/BoxComponent.h"
#include "Components/GGFInteractableComponent.h"

AGGFInteractableDoor::AGGFInteractableDoor()
{
    /* InteractableArea */
    InteractableArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractableArea"));
    InteractableArea->SetupAttachment(RootComponent);
    InteractableArea->InitBoxExtent(FVector(100, 100, 100));
    InteractableArea->SetRelativeLocation(FVector(0, 0, 100));

    /* Interactable Component */
    InteractableComponent = CreateDefaultSubobject<UGGFInteractableComponent>(TEXT("InteractableComponent"));
    InteractableComponent->SetupAttachment(GetInteractableArea());
}

void AGGFInteractableDoor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    /* Interactable Component */
    InteractableComponent->Init(GetInteractableArea(), GetDoorFrameMesh());
    InteractableComponent->OnPawnInteract.AddDynamic(this, &ThisClass::OnPawnInteract);
}

void AGGFInteractableDoor::OnPawnInteract_Implementation(APawn* OtherPawn)
{
    Toggle();
}
