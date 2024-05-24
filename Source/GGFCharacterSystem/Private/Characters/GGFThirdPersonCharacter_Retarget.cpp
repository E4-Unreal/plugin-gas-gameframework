// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFThirdPersonCharacter_Retarget.h"

FName AGGFThirdPersonCharacter_Retarget::RetargetMeshName(TEXT("RetargetMesh"));

AGGFThirdPersonCharacter_Retarget::AGGFThirdPersonCharacter_Retarget()
{
    /* Mesh */
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    CharacterMesh->SetVisibility(false);
    CharacterMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

    /* Retarget Mesh */
    RetargetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(RetargetMeshName);
    RetargetMesh->SetupAttachment(CharacterMesh);
}
