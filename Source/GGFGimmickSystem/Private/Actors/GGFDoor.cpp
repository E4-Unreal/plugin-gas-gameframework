// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFDoor.h"

#include "Components/AudioComponent.h"
#include "Components/GGFTimelineComponent.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

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

    /* Audio Component */
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);

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
        GetAudioComponent()->SetRelativeLocation(FVector(0, -40, 90));
    }

    static ConstructorHelpers::FObjectFinder<USoundCue> OpenSoundFinder(TEXT("/LyraContent/Custom/SoundCues/Effects/SC_Button_01"));
    if (OpenSoundFinder.Succeeded())
    {
        OpenSound = OpenSoundFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundCue> CloseSoundFinder(TEXT("/LyraContent/Custom/SoundCues/Effects/SC_Button_01"));
    if (CloseSoundFinder.Succeeded())
    {
        CloseSound = CloseSoundFinder.Object;
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

bool AGGFDoor::TryActivate_Implementation(AActor* InCauser, AActor* InInstigator)
{
    ++TriggerStack;

    if(TriggerStack == TriggerCount) Open();

    return true;
}

bool AGGFDoor::TryDeactivate_Implementation(AActor* InCauser, AActor* InInstigator)
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

void AGGFDoor::PlaySound(USoundCue* Sound)
{
    // 기존 소리 재생 중지
    auto LocalAudioComponent = GetAudioComponent();
    LocalAudioComponent->Stop();

    // 유효성 검사
    if(Sound == nullptr) return;

    LocalAudioComponent->SetSound(Sound);
    float PlayRate = Sound->Duration / GetTimeline()->Duration;
    LocalAudioComponent->SetPitchMultiplier(PlayRate);
    LocalAudioComponent->Play();
}

void AGGFDoor::Open_Implementation()
{
    bOpen = true;
    GetTimeline()->PlayTimeline();
    PlaySound(OpenSound);
}

void AGGFDoor::Close_Implementation()
{
    bOpen = false;
    GetTimeline()->PlayTimeline(true);
    PlaySound(CloseSound);
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
