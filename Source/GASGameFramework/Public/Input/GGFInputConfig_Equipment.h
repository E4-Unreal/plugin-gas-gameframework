// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Input/GEInputConfig.h"
#include "GGFInputConfig_Equipment.generated.h"

/**
 * 장비창 입력 액션과 장비 슬롯 매핑을 위한 구조체로 EquipmentManager 클래스와 연관되어 있습니다.
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFEquipmentInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UInputAction* InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Equipment.Slot"))
    FGameplayTag SlotTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotIndex;
};

/**
 * 장비창 전용 입력 에셋 설정을 위한 데이터 에셋으로 GGFEquipmentManager에 의존성을 가지고 있습니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFInputConfig_Equipment : public UGEInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
    TArray<FGGFEquipmentInputAction> EquipmentInputActions;

protected:
    virtual void OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;
};
