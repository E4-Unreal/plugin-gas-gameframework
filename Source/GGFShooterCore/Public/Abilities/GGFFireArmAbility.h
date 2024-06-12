// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GGFWeaponAbility.h"
#include "Weapons/GGFFireArm.h"
#include "GGFFireArmAbility.generated.h"

class AGGFFireArm;

/**
 * 총기 전용 어빌리티 클래스
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFFireArmAbility : public UGGFEquipmentAbility
{
    GENERATED_BODY()

protected:

    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;

protected:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE AGGFFireArm* GetFireArm() const { return Cast<AGGFFireArm>(GetEquipment()); }
};
