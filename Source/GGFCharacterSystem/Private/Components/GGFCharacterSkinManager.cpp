// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFCharacterSkinManager.h"

#include "Data/GGFCharacterDataSubsystem.h"

UGGFCharacterSkinManager::UGGFCharacterSkinManager()
{
    // 초기화
    bWantsInitializeComponent = true;
}

void UGGFCharacterSkinManager::InitializeComponent()
{
    Super::InitializeComponent();

    // 기본 스킨 설정
    for (int32 ID : DefaultIDList)
    {
        SetSkinByID(ID);
    }
}

#if WITH_EDITOR
void UGGFCharacterSkinManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    FName PropertyName = PropertyChangedEvent.GetPropertyName();
    if(PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DefaultIDList))
    {
        for (int32 ID : DefaultIDList)
        {
            if(const FGGFCharacterSkinData* NewSkinData = UGGFCharacterDataSubsystem::GetDirectCharacterSkinData(ID))
            {
                SetSkinByData(*NewSkinData);
            }
        }
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UGGFCharacterSkinManager::SetCharacterMesh_Implementation(USkeletalMeshComponent* NewCharacterMesh)
{
    // 입력 유효성 검사
    if(NewCharacterMesh == nullptr) return;

    // 캐릭터 메시 설정
    CharacterMesh = NewCharacterMesh;
}

void UGGFCharacterSkinManager::SetSkinByData_Implementation(const FGGFCharacterSkinData& NewSkinData)
{
    // 입력 유효성 검사
    if(NewSkinData.IsNotValid()) return;

    // 스킨 종류 확인 후 초기화
    switch (NewSkinData.SkinType)
    {
    case EGGFCharacterSkinType::Full:
        if(CharacterMesh.IsValid())
            CharacterMesh->SetSkeletalMesh(NewSkinData.SkeletalMesh);
        break;
    default:
        break;
    }
}

void UGGFCharacterSkinManager::SetSkinByDefinition_Implementation(UGGFCharacterSkinDefinition* NewSkinDefinition)
{
    // 입력 유효성 검사
    if(NewSkinDefinition == nullptr || NewSkinDefinition->IsNotValid()) return;

    // 스킨 설정
    const FGGFCharacterSkinData& NewSkinData = NewSkinDefinition->GetData();
    DefinitionMap.Emplace(NewSkinData.SkinType, NewSkinDefinition);
    SetSkinByData(NewSkinData);
}

void UGGFCharacterSkinManager::SetSkinByID_Implementation(int32 ID)
{
    if(UGameInstance* GameInstance = GetOwner()->GetGameInstance())
    {
        SetSkinByDefinition(GameInstance->GetSubsystem<UGGFCharacterDataSubsystem>()->GetSkinDefinition(ID));
    }
}

void UGGFCharacterSkinManager::Reset_Implementation()
{
    DefinitionMap.Reset();
}

TArray<int32> UGGFCharacterSkinManager::GetCurrentSkinIDList() const
{
    TArray<int32> SkinIDList;
    SkinIDList.Reserve(DefinitionMap.Num());
    for (const auto& [SkinType, Definition] : DefinitionMap)
    {
        if(Definition) SkinIDList.Emplace(Definition->GetID());
    }

    return SkinIDList;
}
