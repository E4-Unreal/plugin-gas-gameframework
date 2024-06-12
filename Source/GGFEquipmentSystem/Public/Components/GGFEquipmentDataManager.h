// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDataManager.h"
#include "GGFEquipmentDataManager.generated.h"

struct FGGFEquipmentData;
class UGGFEquipmentDefinition;

/**
 * 장비 서브 시스템을 사용하기 위한 전용 컴포넌트입니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFEQUIPMENTSYSTEM_API UGGFEquipmentDataManager : public UGGFDataManager
{
    GENERATED_BODY()

protected:
    // 아이템 ID에 대응하는 데이터 에셋
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDefinition, Category = "State", Transient)
    TObjectPtr<UGGFEquipmentDefinition> Definition;

public:
    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FGGFEquipmentData GetData() const;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEquipmentDefinition* GetDefinition() const { return Definition; }

    /* Setter */

    virtual void SetID(int32 NewID) override;
};
