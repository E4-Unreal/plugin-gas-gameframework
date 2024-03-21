// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GEGameplayTags.h"
#include "GameFramework/Actor.h"
#include "GEEquipment.generated.h"

/**
 * GSFEquipmentComponent에서 사용하기 위한 장비 클래스입니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASEXTENSION_API AGEEquipment : public AActor
{
    GENERATED_BODY()

public:
    AGEEquipment();

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
    /* Getter */

    UFUNCTION(BlueprintPure, Category = "Equipment")
    virtual FORCEINLINE FGameplayTag GetEquipmentType() const { return GEGameplayTags::Equipment::EquipmentTag; }

    UFUNCTION(BlueprintPure, Category = "Equipment")
    virtual FORCEINLINE FGameplayTag GetEquipmentSlot() const { return GEGameplayTags::Equipment::SlotTag; }
};
