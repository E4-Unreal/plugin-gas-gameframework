// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFCharacterManager.h"

#include "Data/GGFCharacterDataSubsystem.h"
#include "Data/GGFCharacterDefinition.h"

UGGFCharacterManager::UGGFCharacterManager()
{
    // 초기화
    bWantsInitializeComponent = true;
}

void UGGFCharacterManager::InitializeComponent()
{
    Super::InitializeComponent();

    SetCharacterByID(DefaultID);
}

#if WITH_EDITOR
void UGGFCharacterManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    FName PropertyName = PropertyChangedEvent.GetPropertyName();
    if(PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DefaultID))
    {
        if(const FGGFCharacterData* NewData = UGGFCharacterDataSubsystem::GetDirectCharacterData(DefaultID))
        {
            SetCharacterByData(*NewData);
        }
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif


void UGGFCharacterManager::SetCharacterMesh_Implementation(USkeletalMeshComponent* NewCharacterMesh)
{
    // 입력 유효성 검사
    if(NewCharacterMesh == nullptr) return;

    // 캐릭터 메시 할당
    CharacterMesh = NewCharacterMesh;
}

void UGGFCharacterManager::SetCharacterByData_Implementation(const FGGFCharacterData& NewCharacterData)
{
    // 입력 유효성 검사
    if(NewCharacterData.IsNotValid()) return;

    // 캐릭터 설정
    CharacterMesh->SetSkeletalMesh(NewCharacterData.SkeletalMesh);
    CharacterMesh->SetAnimInstanceClass(NewCharacterData.AnimInstanceClass);
}

void UGGFCharacterManager::SetCharacterByDefinition_Implementation(UGGFCharacterDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr || NewDefinition->IsNotValid()) return;

    // 데이터 에셋 교체
    CharacterDefinition = NewDefinition;

    // 초기화
    SetCharacterByData(NewDefinition->GetData());
}

void UGGFCharacterManager::SetCharacterByID_Implementation(int32 ID)
{
    if(UGameInstance* GameInstance = GetOwner()->GetGameInstance())
    {
        SetCharacterByDefinition(GameInstance->GetSubsystem<UGGFCharacterDataSubsystem>()->GetDefinition(ID));
    }
}
