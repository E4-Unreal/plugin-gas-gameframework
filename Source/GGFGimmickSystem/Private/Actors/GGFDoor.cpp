// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFDoor.h"

AGGFDoor::AGGFDoor()
{
    /* Default SceneComponent */
    DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
    SetRootComponent(DefaultSceneComponent);

    /* Door Mesh */
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(RootComponent);

    /* DoorFrame Mesh */
    DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
    DoorFrameMesh->SetupAttachment(RootComponent);
}

void AGGFDoor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    TransformOffset = DoorMesh->GetRelativeTransform();
}

bool AGGFDoor::Activate_Implementation(AActor* InstigatorActor)
{
    ++TriggerStack;

    if(TriggerStack == TriggerCount) Open();

    return true;
}

bool AGGFDoor::Deactivate_Implementation(AActor* InstigatorActor)
{
    --TriggerStack;

    // TODO 리팩토링
    if(TriggerStack + 1 == TriggerCount) Close();

    return true;
}

void AGGFDoor::OnTimelineActivated_Implementation(float Value)
{
    switch (DoorType)
    {
    case EGGFDoorType::Swing:
        GetDoorMesh()->SetRelativeRotation(TransformOffset.GetRotation().Rotator() + FRotator(0, MaxAngle * Value, 0));
        break;
    case EGGFDoorType::Slide:
        GetDoorMesh()->SetRelativeLocation(TransformOffset.GetLocation() + FVector(0, MaxDistance * Value, 0));
        break;
    case EGGFDoorType::SlideUp:
        GetDoorMesh()->SetRelativeLocation(TransformOffset.GetLocation() + FVector(0, 0, MaxDistance * Value));
        break;
    default:
        break;
    }
}

void AGGFDoor::Open_Implementation()
{
    PlayTimeline();
}

void AGGFDoor::Close_Implementation()
{
    PlayTimeline(true);
}
