// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/GGFInputConfig_Equipment.h"

#include "EnhancedInputComponent.h"
#include "Components/GGFEquipmentManager.h"

void UGGFInputConfig_Equipment::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    // EquipmentManager 유효성 검사
    UGGFEquipmentManager* EquipmentManager = EnhancedInputComponent->GetOwner()->GetComponentByClass<UGGFEquipmentManager>();
    if(EquipmentManager == nullptr) return;

    // 장비창 입력 바인딩
    for (const auto& [InputAction, SlotTag, SlotIndex] : EquipmentInputActions)
    {
        // 유효성 검사
        if(InputAction == nullptr || !SlotTag.IsValid() || SlotIndex < 0) continue;

        // SelectEquipment 바인딩
        EnhancedInputComponent->BindAction(
            InputAction,
            ETriggerEvent::Started,
            EquipmentManager,
            &UGGFEquipmentManager::SelectEquipment,
            SlotTag,
            SlotIndex
            );
    }
}
