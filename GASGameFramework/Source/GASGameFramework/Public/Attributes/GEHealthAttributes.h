// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "GEHealthAttributes.generated.h"

/**
 * 체력과 데미지는 모든 게임에서 사용하는 가장 기본적인 Attribute 입니다.
 * 이 클래스는 매번 작성할 필요없이 범용적으로 사용할 수 있도록 체력, 최대 체력, 체력 재생, 데미지 총 4 가지 어트리뷰트가 포함된 기본 클래스입니다.
 */
UCLASS(Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API UGEHealthAttributes : public UGEAttributeSetBase
{
    GENERATED_BODY()

public:
    // 체력
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(ThisClass, Health)

    // 최대 체력
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth)

    // 체력 재생
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_HealthRegenRate)
    FGameplayAttributeData HealthRegenRate;
    ATTRIBUTE_ACCESSORS(ThisClass, HealthRegenRate)

    // 데미지 (받는 피해량입니다)
    // 서버에서만 사용되는 Meta Attribute로 리플리케이트 되지 않습니다.
    UPROPERTY(BlueprintReadOnly, Category = "Damage")
    FGameplayAttributeData Damage;
    ATTRIBUTE_ACCESSORS(ThisClass, Damage)

public:
    /* UObject */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    /* AttributeSet */

    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
    /* GEAttributeSetBase */

    virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;
    virtual void AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    /* 메서드 */

    // 오버라이드 가능한 데미지 처리 메서드로 Health -= Damage 가 기본 구현되어 있습니다.
    // 자손 클래스에서 Shield Attribute 사용하는 경우 이 메서드를 오버라이드 함으로써 Health 보다 Shield가 먼저 줄어들도록 할 수 있습니다.
    virtual void TakeDamageByGameplayEffect(const FGameplayEffectModCallbackData& Data, const float InDamage);

    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

    UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

    UFUNCTION()
    virtual void OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate);
};
