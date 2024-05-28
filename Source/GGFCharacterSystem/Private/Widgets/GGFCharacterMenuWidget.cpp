// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFCharacterMenuWidget.h"

#include "Components/UniformGridPanel.h"
#include "Data/GGFCharacterDataSubsystem.h"
#include "Interfaces/GGFCharacterInterface.h"
#include "Widgets/GGFCharacterSlotWidget.h"

void UGGFCharacterMenuWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    ConfirmButton->OnClicked.AddDynamic(this, &ThisClass::OnConfirmButtonClicked);
}

void UGGFCharacterMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 초기화
    if(CharacterSlotWidgetClass)
    {
        InitCharacterSlots();
    }
}

void UGGFCharacterMenuWidget::InitCharacterSlots()
{
    // 런타임에만 동작
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFCharacterDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFCharacterDataSubsystem>())
        {
            // 모든 캐릭터 정의 데이터 에셋 가져오기
            CharacterDefinitions = DataSubsystem->GetAllDefinitions();

            // 캐릭터 슬롯 위젯 생성 및 초기화
            CharacterSlotPanel->ClearChildren();
            CharacterSlotWidgets.Reserve(CharacterDefinitions.Num()); // 메모리 할당
            for (int32 Index = 0; Index < CharacterDefinitions.Num(); Index++)
            {
                auto CharacterDefinition = CharacterDefinitions[Index];
                auto NewCharacterSlotWidget = CreateWidget<UGGFCharacterSlotWidget>(GetOwningPlayer(), CharacterSlotWidgetClass);
                NewCharacterSlotWidget->InitCharacterSlot(CharacterDefinition);
                NewCharacterSlotWidget->OnCharacterSelected.AddDynamic(this, &ThisClass::OnSelectButtonClicked);
                CharacterSlotWidgets.Emplace(NewCharacterSlotWidget);
                CharacterSlotPanel->AddChildToUniformGrid(NewCharacterSlotWidget, Index / MaxColumnNum, Index % MaxColumnNum);
            }
        }
    }
}

void UGGFCharacterMenuWidget::OnSelectButtonClicked_Implementation(int32 NewCharacterID)
{
    CharacterID = NewCharacterID;
}

void UGGFCharacterMenuWidget::OnConfirmButtonClicked_Implementation()
{
    // 캐릭터 및 스킨 설정
    if(APawn* OwnerPawn = GetOwningPlayer()->GetPawn())
    {
        if(OwnerPawn->Implements<UGGFCharacterInterface>())
        {
            if(CharacterID >= 0) IGGFCharacterInterface::Execute_SetCharacter(OwnerPawn, CharacterID);
            if(CharacterSkinID >= 0) IGGFCharacterInterface::Execute_SetCharacterSkin(OwnerPawn, CharacterSkinID);
        }
    }

    // 위젯 닫기
    RemoveFromParent();
}
