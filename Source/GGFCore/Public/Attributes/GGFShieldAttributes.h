// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFAttributesBase.h"
#include "GGFShieldAttributes.generated.h"

/**
 * GGFHealthAttributes에서 방어막 어트리뷰트가 추가된 AttributeSet 클래스입니다.
 */
UCLASS(Blueprintable, BlueprintType)
class GGFCORE_API UGGFShieldAttributes : public UGGFAttributesBase
{
    GENERATED_BODY()

public:
    // 방어막
    UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_Shield)
    FGameplayAttributeData Shield;
    ATTRIBUTE_ACCESSORS(ThisClass, Shield)

    // 최대 방어막
    UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_MaxShield)
    FGameplayAttributeData MaxShield;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxShield)

    // 방어막 재생
    UPROPERTY(BlueprintReadOnly, Category = "Shield", ReplicatedUsing = OnRep_ShieldRegenRate)
    FGameplayAttributeData ShieldRegenRate;
    ATTRIBUTE_ACCESSORS(ThisClass, ShieldRegenRate)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GGFAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_Shield(const FGameplayAttributeData& OldShield);

    UFUNCTION()
    virtual void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield);

    UFUNCTION()
    virtual void OnRep_ShieldRegenRate(const FGameplayAttributeData& OldShieldRegenRate);
};
