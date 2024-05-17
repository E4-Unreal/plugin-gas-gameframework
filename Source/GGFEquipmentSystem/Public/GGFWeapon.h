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

    /* 레퍼런스 */

    // 장비 장착 혹은 해제 시 무기 어빌리티를 부여 혹은 제거하기 위한 레퍼런스
    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

protected:
    // 무기를 사용하기 위한 어빌리티로 장착 시에만 부여됩니다.
    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    TArray<TSubclassOf<UGameplayAbility>> WeaponAbilities;

    // 부여된 어빌리티 스펙 핸들
    UPROPERTY(VisibleAnywhere, Category = "State|Weapon", Transient)
    TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

    // OwnerCharacter 유효성 검사
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bOwnerCharacterValid;

public:
    AGGFWeapon();

protected:
    /* 메서드 */
    // 무기 어빌리티를 소유자에게 부여합니다.
    virtual void GiveAbilities();

    // 무기 어빌리티를 소유자로부터 제거합니다.
    virtual void ClearAbilities();

    // 캐릭터 애니메이션 재생
    UFUNCTION(BlueprintCallable)
    virtual void PlayCharacterMontage(UAnimMontage* MontageToPlay);

    /* GSFEquipmentBase */

    virtual void OnEquip_Implementation() override;
    virtual void OnUnEquip_Implementation() override;

protected:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAbilitySystemComponent* GetOwnerAbilitySystem() const { return OwnerAbilitySystem.Get(); }

public:
    /* GGFEquipmentInterface */
    // 무기가 선택된 경우
    virtual void Activate_Implementation() override;

    // 무기가 선택 해제된 경우
    virtual void Deactivate_Implementation() override;
};
