// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFCharacterSlotWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/GGFCharacterDataSubsystem.h"
#include "Data/GGFCharacterDefinition.h"

void UGGFCharacterSlotWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnSelectButtonClicked);
}

void UGGFCharacterSlotWidget::InitCharacterSlot(UGGFCharacterDefinition* InCharacterDefinition)
{
    // 초기화는 한 번만 진행됩니다.
    if(bInitialized) return;

    // 유효성 검사, 런타임에만 호출 가능
    if(InCharacterDefinition == nullptr || InCharacterDefinition->IsNotValid()) return;

    // 초기화 플래그 설정
    bInitialized = true;

    // 초기화 진행
    SetCharacter(InCharacterDefinition);
}

void UGGFCharacterSlotWidget::SetCharacter(UGGFCharacterDefinition* InCharacterDefinition)
{
    // 런타임에서만 호출 가능
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFCharacterDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFCharacterDataSubsystem>())
        {
            // 데이터 에셋 설정
            CharacterDefinition = InCharacterDefinition;
            UpdateCharacterSlot();

            // 사용 가능한 캐릭터 스킨 데이터 에셋 목록 가져오기
            TArray<int32> AvailableSkinIDList = DataSubsystem->GetAvailableSkinIDList(CharacterDefinition->GetID());
            CharacterSKinDefinitions.Reserve(AvailableSkinIDList.Num()); // 메모리 할당
            for (int32 SkinID : AvailableSkinIDList)
            {
                CharacterSKinDefinitions.Emplace(DataSubsystem->GetSkinDefinition(SkinID));
            }
        }
    }
}

void UGGFCharacterSlotWidget::OnSelectButtonClicked_Implementation()
{
    if(CharacterDefinition)
    {
        OnCharacterSelected.Broadcast(CharacterDefinition->GetID());
    }
}

void UGGFCharacterSlotWidget::UpdateCharacterSlot_Implementation()
{
    if(UGGFCharacterDefinition* Definition = GetCharacterDefinition())
    {
        const auto& Data = Definition->GetData();
        ThumbnailImage->SetBrushFromTexture(Data.Thumbnail);
        DisplayNameText->SetText(FText::FromName(Data.DisplayName));
    }
}
