// Fill out your copyright notice in the Description page of Project Settings.


#include "GEHealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UGEHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(Health);
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(MaxHealth);
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(HealthRegenRate);
}

void UGEHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if(Attribute == GetMaxHealthAttribute()) // 최대 체력
    {
        // 체력 비율 유지
        AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
    }
}

void UGEHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;

    if(Attribute == GetHealthAttribute()) // 체력
    {
        // 0 <= 체력 <= 최대 체력
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }
    else if(Attribute == GetMaxHealthAttribute()) // 최대 체력
    {
        // 0 <= 최대 체력
        SetMaxHealth(FMath::Max(GetMaxHealth(), 0.f));
    }
    else if(Attribute == GetDamageAttribute()) // 데미지
    {
        // 로컬 변수로 저장 후 Damage Attribute 값 초기화
        const float LocalDamage = GetDamage();
        SetDamage(0.f);

        // 데미지 처리
        TakeDamageByGameplayEffect(Data, LocalDamage);
    }
}

void UGEHealthAttributeSet::TakeDamageByGameplayEffect(const FGameplayEffectModCallbackData& Data, const float InDamage)
{
    // 데미지 값이 올바르지 않거나 이미 체력이 0인 경우 무시
    if(InDamage <= 0.f || GetHealth() <= 0.f) return;

    // 데미지 적용
    SetHealth(GetHealth() - InDamage);
}

void UGEHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(Health);
}

void UGEHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(MaxHealth);
}

void UGEHealthAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY_SIMPLE(HealthRegenRate);
}
