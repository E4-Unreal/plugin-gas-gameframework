// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFThirdPersonCharacter.h"

#include "Logging.h"
#include "Components/GGFSpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/GGFCameraComponent.h"

FName AGGFThirdPersonCharacter::CameraBoomName(TEXT("CameraBoom"));
FName AGGFThirdPersonCharacter::FollowCameraName(TEXT("FollowCamera"));

AGGFThirdPersonCharacter::AGGFThirdPersonCharacter(const FObjectInitializer& ObjectInitializer)
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
    FollowCamera = CreateDefaultSubobject<UGGFCameraComponent>(FollowCameraName);
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    /* UnrealMannequins 플러그인 에셋 */
    ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshFinder(TEXT("/UnrealMannequins/Mannequin_UE4/Meshes/SKM_Mannequin_UE4.SKM_Mannequin_UE4"));
    if(CharacterMeshFinder.Succeeded()) CharacterMesh->SetSkeletalMeshAsset(CharacterMeshFinder.Object);

    ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimInstanceFinder(TEXT("/UnrealMannequins/Mannequin_UE4/Animations/ABP_Mannequin_UE4.ABP_Mannequin_UE4_C"));
    if(CharacterAnimInstanceFinder.Succeeded()) CharacterMesh->SetAnimInstanceClass(CharacterAnimInstanceFinder.Class);
}

FVector AGGFThirdPersonCharacter::GetTargetLocation_Implementation() const
{
    return CastChecked<UGGFCameraComponent>(GetFollowCamera())->GetTargetLocation();
}
