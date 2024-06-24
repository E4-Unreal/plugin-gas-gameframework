// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEStatsBase.h"
#include "GEMoveSpeedStats.generated.h"

/**
 * 스탯 - 이동 속도
 */
UCLASS()
class GGFCORE_API UGEMoveSpeedStats : public UGEStatsBase
{
    GENERATED_BODY()

public:
    // 이동 속도
    UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
    FGameplayAttributeData MoveSpeed;
    ATTRIBUTE_ACCESSORS(ThisClass, MoveSpeed)

    // 최대 이동 속도 범위
    UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MaxMoveSpeed)
    FGameplayAttributeData MaxMoveSpeed;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxMoveSpeed)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GGFAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);

    UFUNCTION()
    virtual void OnRep_MaxMoveSpeed(const FGameplayAttributeData& OldMaxMoveSpeed);
};
