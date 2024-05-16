// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GGFEquipmentInterface.h"
#include "GGFEquipment.generated.h"

/**
 * GSFEquipmentComponent에서 사용하기 위한 장비 클래스입니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFEQUIPMENTSYSTEM_API AGGFEquipment : public AActor, public IGGFEquipmentInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Equipment", meta = (Categories = "Equipment"))
    FGameplayTag EquipmentType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Equipment", meta = (Categories = "Equipment.Slot"))
    FGameplayTag EquipmentSlot;

public:
    AGGFEquipment();

    /* Actor */

    virtual void SetOwner(AActor* NewOwner) override;
    virtual void OnRep_Owner() override;

protected:
    /* 가상 메서드 */

    UFUNCTION(BlueprintNativeEvent, Category = "Equipment")
    void OnEquip();

    UFUNCTION(BlueprintNativeEvent, Category = "Equipment")
    void OnUnEquip();

    // Owner 상태에 따라 OnEquip 혹은 OnUnEquip을 호출합니다.
    virtual void CheckOwner();

public:
    /* EquipmentInterface */
    virtual void Equip_Implementation(AActor* NewOwner) override;
    virtual void UnEquip_Implementation() override;
    virtual void Activate_Implementation() override;
    virtual void Deactivate_Implementation() override;
    FORCEINLINE virtual const FGameplayTag GetEquipmentSlot_Implementation() const override { return EquipmentSlot; }
    FORCEINLINE virtual const FGameplayTag GetEquipmentType_Implementation() const override { return EquipmentType; }
};
