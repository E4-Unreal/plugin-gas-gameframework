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

    /* ParagonBelica 플러그인 에셋 */
    ConstructorHelpers::FObjectFinder<USkeletalMesh> RetargetMeshFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Meshes/Belica.Belica"));
    if(RetargetMeshFinder.Succeeded()) RetargetMesh->SetSkeletalMeshAsset(RetargetMeshFinder.Object);

    ConstructorHelpers::FClassFinder<UAnimInstance> RetargetAnimInstanceFinder(TEXT("/ParagonBelica/Characters/Heroes/Belica/Rigs/ABP_Retarget_UE4_Belica.ABP_Retarget_UE4_Belica_C"));
    if(RetargetAnimInstanceFinder.Succeeded()) RetargetMesh->SetAnimInstanceClass(RetargetAnimInstanceFinder.Class);
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

bool AGGFThirdPersonCharacter_Retarget::SetCharacterDefinition_Implementation(UGGFCharacterDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr) return false;

    // 데이터 에셋 교체
    CharacterDefinition = NewDefinition;

    // 캐릭터 설정
    const FGGFCharacterData& Data = CharacterDefinition->GetData();
    USkeletalMeshComponent* CharacterMesh = RetargetMesh;
    CharacterMesh->SetSkeletalMesh(Data.SkeletalMesh);
    CharacterMesh->SetAnimInstanceClass(Data.AnimInstanceClass);

    return true;
}

bool AGGFThirdPersonCharacter_Retarget::SetCharacterSkinDefinition_Implementation(
    UGGFCharacterSkinDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr) return false;

    // 데이터 가져오기
    const FGGFCharacterData& CharacterData = CharacterDefinition->GetData();
    const FGGFCharacterSkinData& SkinData = NewDefinition->GetData();

    /* 호환성 검사 */

    // 사용 가능한 캐릭터 목록에 존재하는지 확인
    if(!SkinData.AvailableCharacterIDList.IsEmpty() && !SkinData.AvailableCharacterIDList.Contains(CharacterData.ID)) return false;

    // 사용 불가능한 캐릭터 목록에 존재하는지 확인
    if(!SkinData.ForbiddenCharacterIDList.IsEmpty() && SkinData.ForbiddenCharacterIDList.Contains(CharacterData.ID)) return false;

    /* 설정 */

    // 스킨 종류 확인
    switch (SkinData.SkinType)
    {
    case EGGFCharacterSkinType::Full:
        CharacterSkinDefinitionMap.Emplace(EGGFCharacterSkinType::Full, NewDefinition);
        RetargetMesh->SetSkeletalMesh(SkinData.SkeletalMesh);
        break;
    default:
        return false;
        break;
    }

    return true;
}
