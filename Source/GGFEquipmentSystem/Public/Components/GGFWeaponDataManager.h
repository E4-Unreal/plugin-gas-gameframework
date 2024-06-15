// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFEquipmentDataManager.h"
#include "GGFWeaponDataManager.generated.h"

struct FGGFWeaponData;
class UGGFWeaponDefinition;

/**
 * 무기 데이터 관리를 위한 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFEQUIPMENTSYSTEM_API UGGFWeaponDataManager : public UGGFEquipmentDataManager
{
    GENERATED_BODY()

protected:
    // 무기 데이터 에셋
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetWeaponDefinition, Category = "State", Transient)
    TObjectPtr<UGGFWeaponDefinition> WeaponDefinition;

public:
    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    const FGGFWeaponData& GetWeaponData() const;

protected:
    /* DataManager */

    virtual void FetchData() override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFWeaponDefinition* GetWeaponDefinition() const { return WeaponDefinition; }
};
