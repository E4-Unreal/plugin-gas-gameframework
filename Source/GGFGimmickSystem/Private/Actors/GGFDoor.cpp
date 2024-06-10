// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFDoor.h"

#include "Net/UnrealNetwork.h"

AGGFDoor::AGGFDoor()
{
    /* Default SceneComponent */
    DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
    SetRootComponent(DefaultSceneComponent);

    /* DoorFrame Mesh */
    DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
    DoorFrameMesh->SetupAttachment(RootComponent);

    /* Door Mesh */
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(GetDoorFrameMesh());

    /* 기본 설정 */
    bReplicates = true;

    /* 기본 에셋 설정 */
    static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorFrameMeshFinder(TEXT("/StarterContent/Props/SM_DoorFrame"));
    if (DoorFrameMeshFinder.Succeeded())
    {
        GetDoorFrameMesh()->SetStaticMesh(DoorFrameMeshFinder.Object);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshFinder(TEXT("/StarterContent/Props/SM_Door"));
    if (DoorMeshFinder.Succeeded())
    {
        GetDoorMesh()->SetStaticMesh(DoorMeshFinder.Object);
        GetDoorMesh()->SetRelativeLocation(FVector(0, 45, 0));
    }
}

void AGGFDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, bOpen)
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

void AGGFDoor::Toggle()
{
    if(bOpen)
    {
        Close();
    }
    else
    {
        Open();
    }
}

void AGGFDoor::Open_Implementation()
{
    bOpen = true;
    PlayTimeline();
}

void AGGFDoor::Close_Implementation()
{
    bOpen = false;
    PlayTimeline(true);
}

void AGGFDoor::OnRep_Open(bool bOldOpen)
{
    if(bOpen == bOldOpen) return;

    if(bOpen)
    {
        Open();
    }
    else
    {
        Close();
    }
}
