// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFEquipment.h"
#include "GGFWeapon.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class UAbilitySystemComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFEQUIPMENTSYSTEM_API AGGFWeapon : public AGGFEquipment
{
    GENERATED_BODY()

protected:
    // OwnerCharacter 유효성 검사
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bOwnerCharacterValid;

public:
    AGGFWeapon();

protected:
    /* GSFEquipmentBase */

    virtual void OnEquip_Implementation() override;
    virtual void OnUnEquip_Implementation() override;

    /* 메서드 */

    // 캐릭터 애니메이션 재생
    UFUNCTION(BlueprintCallable)
    virtual void PlayCharacterMontage(UAnimMontage* MontageToPlay);
};
