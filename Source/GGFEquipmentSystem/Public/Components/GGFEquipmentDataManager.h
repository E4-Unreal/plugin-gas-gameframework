// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
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
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetEquipmentDefinition, Category = "State", Transient)
    TObjectPtr<UGGFEquipmentDefinition> EquipmentDefinition;

    // 부여된 장비 스탯 게임플레이 이펙트 핸들
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    FActiveGameplayEffectHandle ActiveStatsEffectHandle;

public:
    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FGGFEquipmentData GetEquipmentData() const;

    // 대상에게 장비 스탯 게임플레이 이펙트 적용
    UFUNCTION(BlueprintCallable)
    virtual void ApplyStatsEffectToTarget(AActor* Target);

    // 대상에게 부여된 장비 스탯 게임플레이 이펙트 제거
    UFUNCTION(BlueprintCallable)
    virtual void RemoveStatsEffectFromTarget(AActor* Target);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGGFEquipmentDefinition* GetEquipmentDefinition() const { return EquipmentDefinition; }

    /* Setter */

    virtual void SetID(int32 NewID) override;
};
