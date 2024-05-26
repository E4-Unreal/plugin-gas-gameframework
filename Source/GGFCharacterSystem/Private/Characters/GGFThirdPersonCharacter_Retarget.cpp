// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFThirdPersonCharacter_Retarget.h"

#include "Components/GGFCharacterManager.h"
#include "Components/GGFCharacterSkinManager.h"
#include "Components/GGFEquipmentManager.h"

FName AGGFThirdPersonCharacter_Retarget::RetargetMeshName(TEXT("RetargetMesh"));

AGGFThirdPersonCharacter_Retarget::AGGFThirdPersonCharacter_Retarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    /* Mesh */
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    CharacterMesh->SetVisibility(false);
    CharacterMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

    /* Retarget Mesh */
    RetargetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(RetargetMeshName);
    RetargetMesh->SetupAttachment(CharacterMesh);

    /* CharacterManager */
    GetCharacterManager()->SetMesh(RetargetMesh);

    /* SkinManager */
    GetSkinManager()->SetCharacterMesh(RetargetMesh);

    /* ParagonBelica 플러그인 에셋 */
    ConstructorHelpers::FObjectFinder<USkeletalMesh> RetargetMeshFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Meshes/Belica.Belica"));
    if(RetargetMeshFinder.Succeeded()) RetargetMesh->SetSkeletalMeshAsset(RetargetMeshFinder.Object);

    ConstructorHelpers::FClassFinder<UAnimInstance> RetargetAnimInstanceFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Rigs/ABP_Retarget_UE4_Belica.ABP_Retarget_UE4_Belica_C"));
    if(RetargetAnimInstanceFinder.Succeeded()) RetargetMesh->SetAnimInstanceClass(RetargetAnimInstanceFinder.Class);
}

void AGGFThirdPersonCharacter_Retarget::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // TODO 생성자로 이동
    /* EquipmentManager */
    GetEquipmentManager()->SetTargetMesh(RetargetMesh);
}

void AGGFThirdPersonCharacter_Retarget::HideBones()
{
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    for (FName BoneName : BoneNamesToHide)
    {
        CharacterMesh->HideBoneByName(BoneName, PBO_None);
        RetargetMesh->HideBoneByName(BoneName, PBO_None);
    }
}
