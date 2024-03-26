// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GGFGameplayTags.h"
#include "GameFramework/Actor.h"
#include "GGFEquipment.generated.h"

/**
 * GSFEquipmentComponent에서 사용하기 위한 장비 클래스입니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API AGGFEquipment : public AActor
{
    GENERATED_BODY()

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
    /* Getter */

    UFUNCTION(BlueprintPure, Category = "Equipment")
    virtual FORCEINLINE FGameplayTag GetEquipmentType() const { return GGFGameplayTags::Equipment::Equipment; }

    UFUNCTION(BlueprintPure, Category = "Equipment")
    virtual FORCEINLINE FGameplayTag GetEquipmentSlot() const { return GGFGameplayTags::Equipment::Slot; }
};
