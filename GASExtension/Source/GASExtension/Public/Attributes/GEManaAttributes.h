// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/GEShieldAttributes.h"
#include "GEManaAttributes.generated.h"

/**
 * GEShieldAttributes에서 마나 어트리뷰트가 추가된 AttributeSet 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API UGEManaAttributes : public UGEShieldAttributes
{
    GENERATED_BODY()

public:
    // 마나
    UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana)
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(ThisClass, Mana)

    // 최대 마나
    UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_MaxMana)
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxMana)

    // 마나 재생
    UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_ManaRegenRate)
    FGameplayAttributeData ManaRegenRate;
    ATTRIBUTE_ACCESSORS(ThisClass, ManaRegenRate)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GEAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);

    UFUNCTION()
    virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

    UFUNCTION()
    virtual void OnRep_ManaRegenRate(const FGameplayAttributeData& OldManaRegenRate);
};
