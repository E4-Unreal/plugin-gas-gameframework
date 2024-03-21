// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\Equipment\GEEquipment.h"
#include "GEWeapon.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class UAbilitySystemComponent;

UCLASS(Abstract, Blueprintable, BlueprintType)
class GASEXTENSION_API AGEWeapon : public AGEEquipment
{
    GENERATED_BODY()

    /* 레퍼런스 */

    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

protected:

    // 무기를 사용하기 위한 어빌리티로 장착 시에만 부여됩니다.
    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    TArray<TSubclassOf<UGameplayAbility>> WeaponAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Weapon", meta = (Categories = "Equipment.Weapon"))
    FGameplayTag WeaponType = GEGameplayTags::Equipment::WeaponTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Weapon", meta = (Categories = "Equipment.Slot"))
    FGameplayTag WeaponSlot = GEGameplayTags::Equipment::SlotTag;

    UPROPERTY(VisibleAnywhere, Category = "State|Weapon", Transient)
    TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

public:
    /* GSFEquipmentBase */

    virtual FGameplayTag GetEquipmentType() const override { return WeaponType; }
    virtual FGameplayTag GetEquipmentSlot() const override { return WeaponSlot; }

protected:
    /* 가상 메서드 */

    // 무기를 장착한 경우 (주 무기로 선택, 즉 손에 쥔 경우)
    UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
    void OnSelected();

    // 무기를 장착 해제한 경우 (주 무기에서 선택 해제, 즉 손이 아닌 다른 곳에 장비하는 경우)
    UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
    void OnDeselected();

    // 무기 어빌리티를 소유자에게 부여합니다.
    virtual void GiveAbilities();

    // 무기 어빌리티를 소유자로부터 제거합니다.
    virtual void ClearAbilities();

    /* GSFEquipmentBase */

    virtual void OnEquip_Implementation() override;
    virtual void OnUnEquip_Implementation() override;
};
