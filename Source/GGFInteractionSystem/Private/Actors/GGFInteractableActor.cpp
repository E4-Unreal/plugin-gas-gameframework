// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableActor.h"

#include "Components/BoxComponent.h"
#include "Components/GGFInteractableComponent.h"

FName AGGFInteractableActor::InteractableComponentName(TEXT("InteractableComponent"));

AGGFInteractableActor::AGGFInteractableActor()
{
    /* Interactable Component */
    InteractableComponent = CreateDefaultSubobject<UGGFInteractableComponent>(TEXT("InteractableComponent"));
    InteractableComponent->SetupAttachment(RootComponent);

    /* 블루프린트 에셋 기본 할당 */
    // LevelPrototyping 플러그인
    static ConstructorHelpers::FObjectFinder<UStaticMesh> DisplayMeshObjectFinder(TEXT("/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube"));
    if(DisplayMeshObjectFinder.Succeeded())
    {
        GetDisplayMesh()->SetStaticMesh(DisplayMeshObjectFinder.Object);
        GetDisplayMesh()->SetRelativeLocation(FVector(0, 0, 50));
    }
}

void AGGFInteractableActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    InteractableComponent->Init(GetTriggerBox(), GetDisplayMesh());
    InteractableComponent->OnPawnInteract.AddDynamic(this, &ThisClass::OnPawnInteract);
    InteractableComponent->OnLocalPawnInteract.AddDynamic(this, &ThisClass::OnLocalPawnInteract);
    InteractableComponent->OnPawnBeginOverlap.AddDynamic(this, &ThisClass::OnPawnBeginOverlap);
    InteractableComponent->OnPawnEndOverlap.AddDynamic(this, &ThisClass::OnPawnEndOverlap);
    InteractableComponent->OnLocalPawnBeginOverlap.AddDynamic(this, &ThisClass::OnLocalPawnBeginOverlap);
    InteractableComponent->OnLocalPawnEndOverlap.AddDynamic(this, &ThisClass::OnLocalPawnEndOverlap);
}

void AGGFInteractableActor::OnPawnInteract_Implementation(APawn* OtherPawn)
{
}

void AGGFInteractableActor::OnLocalPawnInteract_Implementation(APawn* OtherLocalPawn)
{
}

void AGGFInteractableActor::OnPawnBeginOverlap_Implementation(APawn* OtherPawn)
{
}

void AGGFInteractableActor::OnPawnEndOverlap_Implementation(APawn* OtherPawn)
{
}

void AGGFInteractableActor::OnLocalPawnBeginOverlap_Implementation(APawn* OtherLocalPawn)
{
}

void AGGFInteractableActor::OnLocalPawnEndOverlap_Implementation(APawn* OtherLocalPawn)
{
}
