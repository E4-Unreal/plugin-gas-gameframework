// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/GEShieldAttributes.h"

void UGEShieldAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 방어막
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX_AND_REGENRATE(Shield)
}

void UGEShieldAttributes::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 방어막
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Shield)
}

void UGEShieldAttributes::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 방어막
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Shield)
}

void UGEShieldAttributes::TakeDamageByGameplayEffect(const FGameplayEffectModCallbackData& Data, const float InDamage)
{
    // 캐싱
    const float CurrentHealth = GetHealth();
    const float CurrentShield = GetShield();

    // 데미지 적용
    if(CurrentShield >= InDamage)
    {
        // 방어막이 데미지보다 큰 경우 방어막에만 데미지 적용
        SetShield(CurrentShield - InDamage);
    }
    else
    {
        // 방어막에 데미지 우선 적용
        const float HealthDamage = InDamage - CurrentShield;
        SetShield(0.f);

        // 나머지 데미지 적용
        SetHealth(CurrentHealth - HealthDamage);
    }
}

void UGEShieldAttributes::OnRep_Shield(const FGameplayAttributeData& OldShield)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Shield);
}

void UGEShieldAttributes::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxShield);
}

void UGEShieldAttributes::OnRep_ShieldRegenRate(const FGameplayAttributeData& OldShieldRegenRate)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(ShieldRegenRate);
}
