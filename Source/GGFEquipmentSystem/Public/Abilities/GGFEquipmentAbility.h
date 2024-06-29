// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GGFGameplayAbility.h"
#include "Components/GGFEquipmentManager.h"
#include "GGFEquipmentAbility.generated.h"

class UGGFEquipmentManager;

/**
 * 장비 전용 어빌리티
 */
UCLASS()
class GGFEQUIPMENTSYSTEM_API UGGFEquipmentAbility : public UGGFGameplayAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<UGGFEquipmentManager> EquipmentManager;

public:
    /* GameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:
    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;

protected:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE UGGFEquipmentManager* GetEquipmentManager() const { return EquipmentManager.Get(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE AActor* GetEquipment() const { return EquipmentManager->GetSelectedEquipment(); }
};
