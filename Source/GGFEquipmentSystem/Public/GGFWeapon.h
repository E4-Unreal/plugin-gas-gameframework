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

public:
    AGGFWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    /* Equipment */

    virtual void Activate_Implementation() override;
    virtual void Deactivate_Implementation() override;
    virtual void OnIDUpdated(int32 NewID) override;

    /* 메서드 */

    // 캐릭터 애니메이션 재생
    UFUNCTION(BlueprintCallable)
    virtual void PlayCharacterMontage(UAnimMontage* MontageToPlay, float Duration = 1);
};
