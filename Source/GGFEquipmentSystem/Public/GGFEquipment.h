// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GGFEquipmentInterface.h"
#include "GGFEquipment.generated.h"

class UGGFEquipmentDataManager;
class UGameplayEffect;

/**
 * GSFEquipmentComponent에서 사용하기 위한 장비 클래스입니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFEQUIPMENTSYSTEM_API AGGFEquipment : public AActor, public IGGFEquipmentInterface
{
    GENERATED_BODY()

    // 데이터 관리 전용 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDataManager, Category = "Component")
    TObjectPtr<UGGFEquipmentDataManager> DataManager;

    /* 레퍼런스 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetOwnerAbilitySystem, Category = "Reference", Transient)
    TObjectPtr<UAbilitySystemComponent> OwnerAbilitySystem;

protected:
    /* Passive Effect */

    // 장비가 장착되는 즉시 소유자에게 적용될 게임플레이 이펙트 목록입니다.
    // ex) 스탯, 버프 등
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Effects|Equipment")
    TArray<TSubclassOf<UGameplayEffect>> PassiveEffects;

    // 장비가 장착 해제되는 즉시 적용된 게임플레이 이펙트를 제거하기 위한 핸들
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Effects|Equipment", Transient)
    TArray<FActiveGameplayEffectHandle> PassiveEffectSpecHandles;

    /* Passive Ability */

    // 장비가 장착되는 즉시 소유자에게 부여될 게임플레이 어빌리티 목록입니다.
    // ex) 특수 스킬 등
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Abilities|Equipment")
    TArray<TSubclassOf<UGameplayAbility>> PassiveAbilities;

    // 장비가 장착 해제되는 즉시 부여된 게임플레이 어빌리티를 제거하기 위한 핸들
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Abilities|Equipment", Transient)
    TArray<FGameplayAbilitySpecHandle> PassiveAbilitySpecHandles;

    /* Active Effect */

    // 장비가 활성화된 상태에서만 소유자에게 적용될 게임플레이 이펙트 목록입니다.
    // ex) 스탯, 버프 등
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Effects|Equipment")
    TArray<TSubclassOf<UGameplayEffect>> ActiveEffects;

    // 장비가 비활성화될 때 적용된 게임플레이 이펙트를 제거하기 위한 핸들
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Effects|Equipment", Transient)
    TArray<FActiveGameplayEffectHandle> ActiveEffectSpecHandles;

    /* Active Ability */

    // 장비가 활성화된 상태에서만 사용 가능한 게임플레이 어빌리티 목록입니다.
    // ex) 장비 전용 스킬 등
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Abilities|Equipment")
    TArray<TSubclassOf<UGameplayAbility>> ActiveAbilities;

    // 장비가 비활성화될 때 부여된 게임플레이 어빌리티를 제거하기 위한 핸들
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Abilities|Equipment", Transient)
    TArray<FGameplayAbilitySpecHandle> ActiveAbilitySpecHandles;

public:
    AGGFEquipment();

    /* Actor */

    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void PreInitializeComponents() override;
    virtual void PostInitializeComponents() override;

    virtual void SetOwner(AActor* NewOwner) override;
    virtual void OnRep_Owner() override;

    /* EquipmentInterface */

    virtual void Equip_Implementation(AActor* NewOwner) override;
    virtual void UnEquip_Implementation() override;
    virtual void Activate_Implementation() override;
    virtual void Deactivate_Implementation() override;
    virtual const FGameplayTag GetEquipmentSlot_Implementation() const override;
    virtual const FGameplayTag GetEquipmentType_Implementation() const override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintCallable)
    virtual void OnIDUpdated(int32 NewID);

    /* 메서드 */

    UFUNCTION(BlueprintNativeEvent, Category = "Equipment")
    void OnEquip();

    UFUNCTION(BlueprintNativeEvent, Category = "Equipment")
    void OnUnEquip();

    // 소유자에게 어빌리티를 부여합니다.
    UFUNCTION(BlueprintCallable, Category = "Equipment|Abilities")
    virtual void GiveAbilitiesToOwner(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGive, TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles);

    // 소유자로부터 어빌리티를 제거합니다.
    UFUNCTION(BlueprintCallable, Category = "Equipment|Abilities")
    virtual void ClearAbilitiesFromOwner(TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles);

    // 소유자에게 게임플레이 이펙트를 적용합니다.
    UFUNCTION(BlueprintCallable, Category = "Equipment|Effects")
    virtual void ApplyEffectsToOwner(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply, TArray<FActiveGameplayEffectHandle>& EffectSpecHandles);

    // 소유자에게 게임플레이 이펙트를 적용합니다.
    UFUNCTION(BlueprintCallable, Category = "Equipment|Effects")
    virtual void RemoveEffectsFromOwner(TArray<FActiveGameplayEffectHandle>& EffectSpecHandles);

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAbilitySystemComponent* GetOwnerAbilitySystem() const { return OwnerAbilitySystem; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEquipmentDataManager* GetDataManager() const { return DataManager; }
};
