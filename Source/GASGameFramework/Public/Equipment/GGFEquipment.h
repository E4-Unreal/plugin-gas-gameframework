// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GGFGameplayTags.h"
#include "GameFramework/Actor.h"
#include "Interface/GGFEquipmentInterface.h"
#include "GGFEquipment.generated.h"

/**
 * GSFEquipmentComponent에서 사용하기 위한 장비 클래스입니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API AGGFEquipment : public AActor, public IGGFEquipmentInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Equipment", meta = (Categories = "Equipment"))
    FGameplayTag EquipmentType = GGFGameplayTags::Equipment::Equipment;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Equipment", meta = (Categories = "Equipment.Slot"))
    FGameplayTag EquipmentSlot = GGFGameplayTags::Equipment::Slot::Slot;

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

public:
    /* GGFEquipmentInterface */
    FORCEINLINE virtual const FGameplayTag GetEquipmentSlot_Implementation() const override { return EquipmentSlot; }
    FORCEINLINE virtual const FGameplayTag GetEquipmentType_Implementation() const override { return EquipmentType; }
};
