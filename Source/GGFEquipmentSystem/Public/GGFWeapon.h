﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFEquipment.h"
#include "GGFWeapon.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class UAbilitySystemComponent;
class UAnimInstance;

// TODO 삼인칭, 일인칭 설정이 중복되니 구조체 사용?
UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFEQUIPMENTSYSTEM_API AGGFWeapon : public AGGFEquipment
{
    GENERATED_BODY()

    /* 레퍼런스 */

    // 장비 장착 혹은 해제 시 무기 어빌리티를 부여 혹은 제거하기 위한 레퍼런스
    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

    // 무기 관련 캐릭터 애니메이션 재생을 위한 스켈레탈 메시
    TWeakObjectPtr<UAnimInstance> ThirdPersonAnimInstance;
    TWeakObjectPtr<UAnimInstance> FirstPersonAnimInstance;

protected:
    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    TArray<TSubclassOf<UAnimInstance>> ThirdPersonAnimLinkClasses;

    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    TArray<TSubclassOf<UAnimInstance>> FirstPersonAnimLinkClasses;

    // 무기를 사용하기 위한 어빌리티로 장착 시에만 부여됩니다.
    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    TArray<TSubclassOf<UGameplayAbility>> WeaponAbilities;

    UPROPERTY(VisibleAnywhere, Category = "State|Weapon", Transient)
    TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

    /* GGFCameraInterface */
    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    float FOV = 60.f;

    UPROPERTY(EditAnywhere, Category = "Config|Weapon")
    float InterpSpeed = 15.f;

public:
    AGGFWeapon();

protected:
    /* 메서드 */
    // 무기 어빌리티를 소유자에게 부여합니다.
    void GiveAbilities();

    // 무기 어빌리티를 소유자로부터 제거합니다.
    void ClearAbilities();

    // 1인칭 몽타주 애니메이션 재생
    void PlayFirstPersonMontage(UAnimMontage* Montage) const;

    // 1인칭 몽타주 애니메이션 재생
    void PlayThirdPersonMontage(UAnimMontage* Montage) const;

    // 무기 전용 캐릭터 애님 클래스 링크
    void LinkAnimClasses() const;

    // 무기 전용 캐릭터 애님 클래스 링크 제거
    void UnLinkAnimClasses() const;

    /* GSFEquipmentBase */

    virtual void OnEquip_Implementation() override;
    virtual void OnUnEquip_Implementation() override;

private:
    static void LinkCharacterAnimClasses(TWeakObjectPtr<UAnimInstance> AnimInstance, const TArray<TSubclassOf<UAnimInstance>>& AnimLinkClasses);
    static void UnlinkCharacterAnimClasses(TWeakObjectPtr<UAnimInstance> AnimInstance, const TArray<TSubclassOf<UAnimInstance>>& AnimLinkClasses);

protected:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAbilitySystemComponent* GetOwnerAbilitySystem() const { return OwnerAbilitySystem.Get(); }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAnimInstance* GetThirdPersonAnimInstance() const { return ThirdPersonAnimInstance.Get(); }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAnimInstance* GetFirstPersonAnimInstance() const { return FirstPersonAnimInstance.Get(); }

public:
    /* GGFEquipmentInterface */
    // 무기가 선택된 경우
    virtual void Activate_Implementation() override;

    // 무기가 선택 해제된 경우
    virtual void Deactivate_Implementation() override;
};