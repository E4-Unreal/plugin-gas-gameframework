// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GGFWeaponAbility.h"
#include "GGFFireArmAbility.generated.h"

class AGGFFireArm;
/**
 * 총기 전용 어빌리티 클래스
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFFireArmAbility : public UGGFWeaponAbility
{
    GENERATED_BODY()

    TWeakObjectPtr<AGGFFireArm> FireArm;

public:
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

protected:
    /* GGFWeaponAbility */
    virtual void OnRep_Weapon() override;

    /* Getter */
    UFUNCTION(BlueprintCallable)
    FORCEINLINE AGGFFireArm* GetFireArm() const { return FireArm.Get(); }
};
