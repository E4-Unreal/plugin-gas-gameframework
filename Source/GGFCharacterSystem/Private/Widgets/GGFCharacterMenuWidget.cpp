// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFCharacterMenuWidget.h"

#include "Components/UniformGridPanel.h"
#include "Data/GGFCharacterDataSubsystem.h"
#include "Data/GGFCharacterSkinDefinition.h"
#include "Interfaces/GGFCharacterInterface.h"
#include "Widgets/GGFCharacterSlotWidget.h"

void UGGFCharacterMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // 이벤트 바인딩
    ConfirmButton->OnClicked.AddDynamic(this, &ThisClass::OnConfirmButtonClicked);
    SkinComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnSkinComboBoxSelectionChanged);

    // 프리뷰 초기화
    Clear();

    // 초기화
    if(CharacterSlotWidgetClass)
    {
        InitCharacterSlots();
    }
}

void UGGFCharacterMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if(APawn* OwnerPawn = GetOwningPlayerPawn())
    {
        if(OwnerPawn->Implements<UGGFCharacterInterface>())
        {
            OnSelectButtonClicked(IGGFCharacterInterface::Execute_GetCharacterID(OwnerPawn));

            // TODO 부위별, 현재는 풀 스킨만 고려
            TArray<int32> SkinIDList = IGGFCharacterInterface::Execute_GetCharacterSkinIDList(OwnerPawn);
            if(auto DataSubsystem = GetGameInstance()->GetSubsystem<UGGFCharacterDataSubsystem>())
            {
                for (auto ID : SkinIDList)
                {
                    if(auto CharacterSkin = DataSubsystem->GetSkinDefinition(ID))
                    {
                        if(CharacterSkin->GetData().SkinType == EGGFCharacterSkinType::Full)
                        {
                            SkinComboBox->SetSelectedOption(CharacterSkin->GetData().DisplayName.ToString());
                        }
                    }
                }
            }
        }
    }
}

void UGGFCharacterMenuWidget::Clear()
{
    // CharacterSlotPanel
    CharacterSlotPanel->ClearChildren();

    // SkinComboBox
    SkinComboBox->ClearOptions();
    SkinComboBox->ClearSelection();
}

void UGGFCharacterMenuWidget::InitCharacterSlots()
{
    if(!CharacterSlotWidgets.IsEmpty()) return;

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

    // 스킨 선택 콤보 박스 업데이트
    if(UGameInstance* GameInstance = GetGameInstance())
    {
        if(UGGFCharacterDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UGGFCharacterDataSubsystem>())
        {
            // TODO 데이터 서브 시스템에서 캐싱
            // 사용 가능한 캐릭터 스킨 데이터 에셋 ID 가져오기
            const TArray<int32> SkinIDList = DataSubsystem->GetAvailableSkinIDList(CharacterID);

            // 모든 캐릭터 정의 데이터 에셋 가져오기
            TArray<UGGFCharacterSkinDefinition*> SkinDefinitions;
            SkinDefinitions.Reserve(SkinIDList.Num());
            for (auto SkinID : SkinIDList)
            {
                SkinDefinitions.Emplace(DataSubsystem->GetSkinDefinition(SkinID));
            }

            // 콤보 박스 초기화
            SkinComboBox->ClearOptions();
            SkinComboBox->ClearSelection();
            SkinIDMap.Reset();

            // 옵션에 기본 스킨 추가
            FString DefaultSkinNameString = "Default";
            SkinComboBox->AddOption(DefaultSkinNameString);

            // TODO 현재 장착된 스킨 옵션 선택
            SkinComboBox->SetSelectedOption(DefaultSkinNameString);

            // 콤보 박스 갱신
            for (auto SkinDefinition : SkinDefinitions)
            {
                const auto& SkinData = SkinDefinition->GetData();
                FString DisplayNameString = SkinData.DisplayName.ToString();
                SkinComboBox->AddOption(DisplayNameString);
                SkinIDMap.Emplace(DisplayNameString, SkinDefinition->GetID());
            }
        }
    }
}

void UGGFCharacterMenuWidget::OnSkinComboBoxSelectionChanged(FString SelectedItem,
    ESelectInfo::Type SelectionType)
{
    if(SkinIDMap.Contains(SelectedItem))
    {
        // 스킨 ID 설정
        CharacterSkinID = SkinIDMap[SelectedItem];
    }
    else
    {
        // 기본 스킨 ID 설정
        CharacterSkinID = -1;
    }
}

void UGGFCharacterMenuWidget::OnConfirmButtonClicked_Implementation()
{
    // 캐릭터 및 스킨 설정
    if(APawn* OwnerPawn = GetOwningPlayerPawn())
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
