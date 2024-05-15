// Fill out your copyright notice in the Description page of Project Settings.

#include "TSPlayerCharacter.h"

#include "TSPlayerAbilitySystem.h"
#include "Camera/CameraComponent.h"
#include "Character/Components/GGFSpringArmComponent.h"
#include "Components/CapsuleComponent.h"

FName ATSPlayerCharacter::CameraBoomName(TEXT("CameraBoom"));
FName ATSPlayerCharacter::FollowCameraName(TEXT("FollowCamera"));

ATSPlayerCharacter::ATSPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass(AbilitySystemName, UTSPlayerAbilitySystem::StaticClass()))
{
    /* Character */
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    /* CapsuleComponent */
    const float CapsuleHalfHeight = 94;
    UCapsuleComponent* Capsule = GetCapsuleComponent();
    Capsule->InitCapsuleSize(42, CapsuleHalfHeight);

    /* Mesh */
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    CharacterMesh->SetRelativeRotation(FRotator(0, -90, 0));
    CharacterMesh->SetRelativeLocation(FVector(0, 0, -CapsuleHalfHeight));

    /* Camera Boom */
    CameraBoom = CreateDefaultSubobject<UGGFSpringArmComponent>(CameraBoomName);
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 350;
    CameraBoom->SocketOffset = FVector(0, 75, 75);
    CameraBoom->bUsePawnControlRotation = true;

    /* Follow Camera */
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(FollowCameraName);
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}
