// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/GEHealthAttributes.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"

void UGEHealthAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY_WITH_MAX_AND_REGENRATE(Health)
}

void UGEHealthAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;

    if(Attribute == GetDamageAttribute()) // 데미지
    {
        // 로컬 변수로 저장 후 Damage Attribute 값 초기화
        const float LocalDamage = GetDamage();
        SetDamage(0.f);

        // 데미지 값이 음수이거나 이미 체력이 0인 경우 무시
        if(LocalDamage <= 0.f || GetHealth() <= 0.f) return;

        // 데미지 처리
        TakeDamageByGameplayEffect(Data, LocalDamage);
    }
}

void UGEHealthAttributes::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    // 체력
    CLAMP_ATTRIBUTE_AND_MAX_ATTRIBUTE(Attribute, NewValue, Health)
}

void UGEHealthAttributes::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    // 체력
    ADJUST_ATTRIBUTE_FOR_MAX_ATTRIBUTE_CHANGE(Health)
}

void UGEHealthAttributes::TakeDamageByGameplayEffect(const FGameplayEffectModCallbackData& Data, const float InDamage)
{
    // 데미지 적용
    SetHealth(GetHealth() - InDamage);
}

void UGEHealthAttributes::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Health);
}

void UGEHealthAttributes::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxHealth);
}

void UGEHealthAttributes::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(HealthRegenRate);
}
