// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GGFCharacterSlotWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UGGFCharacterSkinDefinition;
class UGGFCharacterDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelectedSignature, int32, CharacterID);

/**
 * CharacterMenuWidget에서 사용하기 위한 캐릭터 선택 슬롯 위젯 클래스입니다.
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFCharacterSlotWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnCharacterSelectedSignature OnCharacterSelected;

private:
    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    bool bInitialized;

    // 캐릭터 정의 데이터 에셋
    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TObjectPtr<UGGFCharacterDefinition> CharacterDefinition;

    // 사용 가능한 캐릭터 스킨 데이터 에셋 목록
    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TArray<TObjectPtr<UGGFCharacterSkinDefinition>> CharacterSKinDefinitions;

    /* 위젯 */

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ThumbnailImage;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DisplayNameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> SelectButton;

public:
    /* UserWidget */

    virtual void NativePreConstruct() override;

    // 초기화
    UFUNCTION(BlueprintCallable)
    void InitCharacterSlot(UGGFCharacterDefinition* InCharacterDefinition);

protected:
    UFUNCTION(BlueprintCallable)
    virtual void SetCharacter(UGGFCharacterDefinition* InCharacterDefinition);

    UFUNCTION(BlueprintNativeEvent)
    void OnSelectButtonClicked();

protected:
    UFUNCTION(BlueprintNativeEvent)
    void UpdateCharacterSlot();

    // 초기화 진행 여부
    UFUNCTION(BlueprintPure)
    bool IsInitialized() const { return bInitialized; }

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    UGGFCharacterDefinition* GetCharacterDefinition() const { return CharacterDefinition; }

    UFUNCTION(BlueprintGetter)
    const TArray<UGGFCharacterSkinDefinition*>& GetCharacterSKinDefinitions() const { return CharacterSKinDefinitions; }
};
