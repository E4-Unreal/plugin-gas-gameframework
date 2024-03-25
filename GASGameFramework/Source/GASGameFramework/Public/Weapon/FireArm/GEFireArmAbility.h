// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/GEWeaponAbility.h"
#include "GEFireArmAbility.generated.h"

class AGEFireArm;
/**
 * 총기 전용 어빌리티 클래스
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGEFireArmAbility : public UGEWeaponAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<AGEFireArm> FireArm;

protected:
    /* GEWeaponAbility */
    virtual void OnRep_Weapon() override;

    /* Getter */
    UFUNCTION(BlueprintCallable)
    FORCEINLINE AGEFireArm* GetFireArm() const { return FireArm.Get(); }
};
