// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFStatsBase.h"
#include "GGFAttackStats.generated.h"

/**
 * 스탯 - 공격력
 */
UCLASS()
class GGFCORE_API UGGFAttackStats : public UGGFStatsBase
{
    GENERATED_BODY()

public:
    // 공격력
    UPROPERTY(BlueprintReadOnly, Category = "Attack", ReplicatedUsing = OnRep_Attack)
    FGameplayAttributeData Attack;
    ATTRIBUTE_ACCESSORS(ThisClass, Attack)

    // 최대 공격력 범위
    UPROPERTY(BlueprintReadOnly, Category = "Attack", ReplicatedUsing = OnRep_MaxAttack)
    FGameplayAttributeData MaxAttack;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxAttack)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GGFAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);

    UFUNCTION()
    virtual void OnRep_MaxAttack(const FGameplayAttributeData& OldMaxAttack);
};
