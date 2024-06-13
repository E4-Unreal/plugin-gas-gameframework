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
    // 장착 중인 상태
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bEquipping = false;

    FTimerHandle EquipTimerHandle;

protected:
    /* Equipment */

    virtual void Activate_Implementation() override;
    virtual void Deactivate_Implementation() override;
    virtual void OnIDUpdated(int32 NewID) override;

    /* 메서드 */

    UFUNCTION()
    virtual void FinishEquipping();

    // 무기 애님 몽타주 재생
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void PlayAnimMontage(UAnimMontage* NewAnimMontage, float Duration = 0) const;

    // 캐릭터 애님 클래스 변경
    UFUNCTION(BlueprintCallable, Category = "Character")
    virtual void SetCharacterAnimClass(TSubclassOf<UAnimInstance> NewAnimClass) const;

    // 캐릭터 애님 몽타주 재생
    UFUNCTION(BlueprintCallable, Category = "Character")
    virtual void PlayCharacterAnimMontage(UAnimMontage* NewAnimMontage, float Duration = 0) const;
};
