// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Widgets/GGFInteractionMenuWidget.h"
#include "GGFCharacterMenuWidget.generated.h"

class UUniformGridPanel;
class UGGFCharacterDefinition;
class UGGFCharacterSlotWidget;

// TODO 나중에 틀이 갖춰지면 기능 전용 클래스와 특정 UI 컨트롤 전용 클래스로 분리
/**
 * 캐릭터 및 스킨 선택을 위한 위젯 클래스
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFCharacterMenuWidget : public UGGFInteractionMenuWidget
{
    GENERATED_BODY()

    // 캐릭터 정의 데이터 에셋 목록
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCharacterDefinitions, Category = "Reference", Transient)
    TArray<TObjectPtr<UGGFCharacterDefinition>> CharacterDefinitions;

    // 캐릭터 슬롯 위젯 인스턴스 목록
    UPROPERTY(VisibleAnywhere, Category = "Component", Transient)
    TArray<TObjectPtr<UGGFCharacterSlotWidget>> CharacterSlotWidgets;

    /* 디자인 */

    // 캐릭터 슬롯 표시를 위한 패널
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUniformGridPanel> CharacterSlotPanel;

    // 캐릭터 및 스킨 설정을 위한 버튼
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ConfirmButton;

protected:
    // 캐릭터 선택을 위한 슬롯 위젯 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UGGFCharacterSlotWidget> CharacterSlotWidgetClass;

    // 캐릭터 슬롯 패널 최대 열 수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 MaxColumnNum = 4;

    // 선택된 캐릭터 ID
    int32 CharacterID = -1;

    // 선택된 캐릭터 스킨 ID
    int32 CharacterSkinID = -1;

protected:
    /* UserWidget */

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;

    /* 메서드 */

    // 캐릭터 슬롯 위젯 초기화
    virtual void InitCharacterSlots();

    // 캐릭터 슬롯 버튼 클릭 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnSelectButtonClicked(int32 NewCharacterID);

    // 결정 버튼 클릭 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnConfirmButtonClicked();

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    const TArray<UGGFCharacterDefinition*>& GetCharacterDefinitions() const { return CharacterDefinitions; }

    UFUNCTION(BlueprintGetter)
    const TArray<UGGFCharacterSlotWidget*>& GetCharacterSlotWidgets() const { return CharacterSlotWidgets; }
};
