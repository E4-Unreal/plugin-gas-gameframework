// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GGFWeaponDataManager.h"
#include "Data/GGFFireArmDefinition.h"
#include "GGFFireArmDataManager.generated.h"

class UGGFFireArmDefinition;

/**
 * 총기 데이터 관리를 위한 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFSHOOTERCORE_API UGGFFireArmDataManager : public UGGFWeaponDataManager
{
    GENERATED_BODY()

protected:
    // 총기 전용 데이터 에셋
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetFireArmDefinition, Category = "State", Transient)
    TObjectPtr<UGGFFireArmDefinition> FireArmDefinition;

public:
    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FGGFFireArmData GetFireArmData() const;

protected:
    /* DataManager */

    virtual void FetchData() override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFFireArmDefinition* GetFireArmDefinition() const { return FireArmDefinition; }
};
