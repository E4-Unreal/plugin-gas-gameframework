// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFPickupEquipment.h"

#include "Abilities/GGFEquipmentAbility.h"

void AGGFPickupEquipment::OnPawnInteract_Implementation(APawn* OtherPawn)
{
    Super::OnPawnInteract_Implementation(OtherPawn);

    // 서버에서 장비 추가 성공 시 파괴
    if(OtherPawn->HasAuthority())
    {
        if(auto EquipmentManager = OtherPawn->GetComponentByClass<UGGFEquipmentManager>())
        {
            if(EquipmentManager->AddEquipmentByID(EquipmentID))
            {
                Destroy();
            }
        }
    }
}
