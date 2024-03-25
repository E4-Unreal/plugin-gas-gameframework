// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFManaAttributes.h"
#include "GGFStaminaAttributes.generated.h"

/**
 * GGFManaAttributes에서 스태미나 어트리뷰트가 추가된 AttributeSet 클래스입니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFStaminaAttributes : public UGGFManaAttributes
{
    GENERATED_BODY()

public:
    // 마나
    UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_Stamina)
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(ThisClass, Stamina)

    // 최대 마나
    UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_MaxStamina)
    FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxStamina)

    // 마나 재생
    UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing = OnRep_StaminaRegenRate)
    FGameplayAttributeData StaminaRegenRate;
    ATTRIBUTE_ACCESSORS(ThisClass, StaminaRegenRate)

public:
    /* UObject */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    /* GGFAttributeSetBase */
    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 리플리케이트 */
    UFUNCTION()
    virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

    UFUNCTION()
    virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

    UFUNCTION()
    virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldStaminaRegenRate);
};
