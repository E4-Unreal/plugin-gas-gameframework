// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFThirdPersonCharacter_Retarget.h"

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

    /* ParagonBelica 플러그인 에셋 */
    ConstructorHelpers::FObjectFinder<USkeletalMesh> RetargetMeshFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Meshes/Belica.Belica"));
    if(RetargetMeshFinder.Succeeded()) RetargetMesh->SetSkeletalMeshAsset(RetargetMeshFinder.Object);

    ConstructorHelpers::FClassFinder<UAnimInstance> RetargetAnimInstanceFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Rigs/ABP_Retarget_UE4_Belica.ABP_Retarget_UE4_Belica_C"));
    if(RetargetAnimInstanceFinder.Succeeded()) RetargetMesh->SetAnimInstanceClass(RetargetAnimInstanceFinder.Class);
}

void AGGFThirdPersonCharacter_Retarget::PostInitializeComponents()
{
    Super::PostInitializeComponents();

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

/* GGFCharacterInterface */

bool AGGFThirdPersonCharacter_Retarget::SetCharacterData_Implementation(const FGGFCharacterData& NewCharacterData)
{
    // 입력 유효성 검사
    if(NewCharacterData.IsNotValid()) return false;

    // 캐릭터 설정
    USkeletalMeshComponent* CharacterMesh = RetargetMesh;
    CharacterMesh->SetSkeletalMesh(NewCharacterData.SkeletalMesh);
    CharacterMesh->SetAnimInstanceClass(NewCharacterData.AnimInstanceClass);

    return true;
}

/* GGFCharacterSkinInterface */

bool AGGFThirdPersonCharacter_Retarget::SetCharacterSkinData_Implementation(
    const FGGFCharacterSkinData& NewCharacterSkinData)
{
    // 입력 유효성 검사
    if(NewCharacterSkinData.IsNotValid()) return false;

    // 캐릭터 ID
    int32 CharacterID = CharacterDefinition && CharacterDefinition->IsValid() ? CharacterDefinition->GetID() : DefaultCharacterID;

    // 사용 가능한 캐릭터 목록에 존재하는지 확인
    if(!NewCharacterSkinData.AvailableCharacterIDList.IsEmpty() && !NewCharacterSkinData.AvailableCharacterIDList.Contains(CharacterID)) return false;

    // 사용 불가능한 캐릭터 목록에 존재하는지 확인
    if(!NewCharacterSkinData.ForbiddenCharacterIDList.IsEmpty() && NewCharacterSkinData.ForbiddenCharacterIDList.Contains(CharacterID)) return false;

    // 스킨 종류 확인 후 초기화
    switch (NewCharacterSkinData.SkinType)
    {
    case EGGFCharacterSkinType::Full:
        RetargetMesh->SetSkeletalMesh(NewCharacterSkinData.SkeletalMesh);
        break;
    default:
        return false;
        break;
    }

    return true;
}
