// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFThirdPersonCharacter_Retarget.h"

#include "Logging.h"

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

    /* ParagonBelica 플러그인 에셋 */
    ConstructorHelpers::FObjectFinder<USkeletalMesh> RetargetMeshFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Meshes/Belica.Belica"));
    if(RetargetMeshFinder.Succeeded()) RetargetMesh->SetSkeletalMeshAsset(RetargetMeshFinder.Object);

    ConstructorHelpers::FClassFinder<UAnimInstance> RetargetAnimInstanceFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Rigs/ABP_Retarget_UE4_Belica.ABP_Retarget_UE4_Belica_C"));
    if(RetargetAnimInstanceFinder.Succeeded()) RetargetMesh->SetAnimInstanceClass(RetargetAnimInstanceFinder.Class);
}

bool AGGFThirdPersonCharacter_Retarget::SetFullSkin_Implementation(USkeletalMesh* FullSkin)
{
    // 입력 유효성 검사
    if(FullSkin == nullptr) return false;

#if WITH_EDITOR
    // 스켈레톤 호환 검사
    if(USkeletalMesh* CurrentMesh = RetargetMesh->GetSkeletalMeshAsset())
    {
        if(!CurrentMesh->GetSkeleton()->IsCompatibleForEditor(FullSkin->GetSkeleton()))
        {
            UE_LOG(LogGGFCharacterSystem, Warning, TEXT("%s의 스켈레톤은 %s의 스켈레톤과 호환되지 않습니다."), *FullSkin->GetName(), *CurrentMesh->GetName());
        }
    }
#endif

    // 스켈레탈 메시 에셋 교체
    RetargetMesh->SetSkeletalMesh(FullSkin);

    return true;
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
