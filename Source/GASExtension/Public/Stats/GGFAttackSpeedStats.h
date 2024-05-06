// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/GGFAttributeSetBase.h"
#include "GGFAttackSpeedStats.generated.h"

/**
 * 스탯 - 공격 속도
 */
UCLASS()
class GASEXTENSION_API UGGFAttackSpeedStats : public UGGFAttributeSetBase
{
    GENERATED_BODY()

public:
    // 공격 속도
    UPROPERTY(BlueprintReadOnly, Category = "AttackSpeed", ReplicatedUsing = OnRep_AttackSpeed)
    FGameplayAttributeData AttackSpeed;
    ATTRIBUTE_ACCESSORS(ThisClass, AttackSpeed)

    // 최대 공격 속도 범위
    UPROPERTY(BlueprintReadOnly, Category = "AttackSpeed", ReplicatedUsing = OnRep_MaxAttackSpeed)
    FGameplayAttributeData MaxAttackSpeed;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxAttackSpeed)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GGFAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);

    UFUNCTION()
    virtual void OnRep_MaxAttackSpeed(const FGameplayAttributeData& OldMaxAttackSpeed);
};
