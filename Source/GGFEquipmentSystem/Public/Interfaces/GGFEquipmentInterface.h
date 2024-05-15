// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "GGFEquipmentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class GGFEQUIPMENTSYSTEM_API UGGFEquipmentInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * EquipmentManager에서 장착 가능한 장비 슬롯을 검사하기 위한 인터페이스입니다.
 */
class GGFEQUIPMENTSYSTEM_API IGGFEquipmentInterface
{
    GENERATED_BODY()

public:
    // 장비를 활성화합니다. 주로 해당 장비가 선택되었을 때 어빌리티를 부여하기 위해 사용됩니다.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GGFEquipmentInterface")
    void Activate();

    // 장비를 비활성화합니다. 주로 해당 장비가 선택 해제되었을 때 어빌리티를 제거하기 위해 사용됩니다.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GGFEquipmentInterface")
    void Deactivate();

    /* Getter */
    // 장비 슬롯
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GGFEquipmentInterface")
    const FGameplayTag GetEquipmentSlot() const;

    // TODO 현재 사용하고 있지 않은 상태이며 추후에 ItemInterface의 ItemType으로 이전될 수 있습니다.
    // 장비 종류
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GGFEquipmentInterface")
    const FGameplayTag GetEquipmentType() const;
};
