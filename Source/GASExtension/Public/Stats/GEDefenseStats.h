// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEStatsBase.h"
#include "GEDefenseStats.generated.h"

/**
 * 스탯 - 방어력
 */
UCLASS()
class GASEXTENSION_API UGEDefenseStats : public UGEStatsBase
{
    GENERATED_BODY()

public:
    // 방어력
    UPROPERTY(BlueprintReadOnly, Category = "Defense", ReplicatedUsing = OnRep_Defense)
    FGameplayAttributeData Defense;
    ATTRIBUTE_ACCESSORS(ThisClass, Defense)

    // 최대 방어력 범위
    UPROPERTY(BlueprintReadOnly, Category = "Defense", ReplicatedUsing = OnRep_MaxDefense)
    FGameplayAttributeData MaxDefense;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxDefense)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GGFAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);

    UFUNCTION()
    virtual void OnRep_MaxDefense(const FGameplayAttributeData& OldMaxDefense);
};
