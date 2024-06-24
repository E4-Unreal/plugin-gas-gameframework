// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEStatsBase.h"
#include "GEAbilityHasteStats.generated.h"

/**
 * 스탯 - 스킬 가속
 */
UCLASS()
class GGFCORE_API UGEAbilityHasteStats : public UGEStatsBase
{
    GENERATED_BODY()

public:
    // 스킬 가속
    UPROPERTY(BlueprintReadOnly, Category = "AbilityHaste", ReplicatedUsing = OnRep_AbilityHaste)
    FGameplayAttributeData AbilityHaste;
    ATTRIBUTE_ACCESSORS(ThisClass, AbilityHaste)

    // 최대 스킬 가속 범위
    UPROPERTY(BlueprintReadOnly, Category = "AbilityHaste", ReplicatedUsing = OnRep_MaxAbilityHaste)
    FGameplayAttributeData MaxAbilityHaste;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxAbilityHaste)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GGFAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste);

    UFUNCTION()
    virtual void OnRep_MaxAbilityHaste(const FGameplayAttributeData& OldMaxAbilityHaste);
};
