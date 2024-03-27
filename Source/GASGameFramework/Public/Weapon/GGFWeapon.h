// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/GGFEquipment.h"
#include "Interface/GGFCameraInterface.h"
#include "GGFWeapon.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class UAbilitySystemComponent;
class UAnimInstance;

UCLASS(Abstract, Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API AGGFWeapon : public AGGFEquipment, public IGGFCameraInterface
{
    GENERATED_BODY()

    /* 레퍼런스 */

    // 장비 장착 혹은 해제 시 무기 어빌리티를 부여 혹은 제거하기 위한 레퍼런스
    TWeakObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

    // 무기 관련 캐릭터 애니메이션 재생을 위한 스켈레탈 메시
    TWeakObjectPtr<USkeletalMeshComponent> ThirdPersonMesh;
    TWeakObjectPtr<USkeletalMeshComponent> FirstPersonMesh;

protected:

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
    /* 가상 메서드 */

    // 무기 어빌리티를 소유자에게 부여합니다.
    virtual void GiveAbilities();

    // 무기 어빌리티를 소유자로부터 제거합니다.
    virtual void ClearAbilities();

    /* GSFEquipmentBase */

    virtual void OnEquip_Implementation() override;
    virtual void OnUnEquip_Implementation() override;

protected:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAbilitySystemComponent* GetOwnerAbilitySystem() const { return OwnerAbilitySystem.Get(); }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetThirdPersonMesh() const { return ThirdPersonMesh.Get(); }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAnimInstance* GetThirdPersonAnimInstance() const { return ThirdPersonMesh.IsValid() ? ThirdPersonMesh.Get()->GetAnimInstance() : nullptr; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh.Get(); }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAnimInstance* GetFirstPersonAnimInstance() const { return FirstPersonMesh.IsValid() ? FirstPersonMesh.Get()->GetAnimInstance() : nullptr; }

public:
    /* GGFEquipmentInterface */
    // 무기가 선택된 경우
    virtual void Activate_Implementation() override;

    // 무기가 선택 해제된 경우
    virtual void Deactivate_Implementation() override;

    /* GGFCameraInterface */
    FORCEINLINE virtual float GetFieldOfView_Implementation() const override { return FOV; }
    FORCEINLINE virtual float GetInterpSpeed_Implementation() const override { return InterpSpeed; }
};
