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

    SetID(DefaultID);
}

#if WITH_EDITOR
void UGGFCharacterManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    FName PropertyName = PropertyChangedEvent.GetPropertyName();
    if(PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DefaultID))
    {
        if(FGGFCharacterData* NewData = UGGFCharacterDataSubsystem::GetDirectCharacterData(DefaultID))
        {
            SetData(*NewData);
        }
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif


void UGGFCharacterManager::SetMesh_Implementation(USkeletalMeshComponent* NewMesh)
{
    // 입력 유효성 검사
    if(NewMesh == nullptr) return;

    // 캐릭터 메시 할당
    Mesh = NewMesh;
}

void UGGFCharacterManager::SetData_Implementation(const FGGFCharacterData& NewCharacterData)
{
    // 입력 유효성 검사
    if(NewCharacterData.IsNotValid()) return;

    // 캐릭터 설정
    Mesh->SetSkeletalMesh(NewCharacterData.SkeletalMesh);
    Mesh->SetAnimInstanceClass(NewCharacterData.AnimInstanceClass);
}

void UGGFCharacterManager::SetDefinition_Implementation(UGGFCharacterDefinition* NewDefinition)
{
    // 입력 유효성 검사
    if(NewDefinition == nullptr || NewDefinition->IsNotValid()) return;

    // 데이터 에셋 교체
    CharacterDefinition = NewDefinition;

    // 초기화
    SetData(NewDefinition->GetData());
}

void UGGFCharacterManager::SetID_Implementation(int32 ID)
{
    if(UGameInstance* GameInstance = GetOwner()->GetGameInstance())
    {
        SetDefinition(GameInstance->GetSubsystem<UGGFCharacterDataSubsystem>()->GetDefinition(ID));
    }
}
