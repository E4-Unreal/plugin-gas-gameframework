// Fill out your copyright notice in the Description page of Project Settings.

#include "GEHealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

// 게임 플레이 태그 정의
namespace GEGameplayTags
{
    UE_DEFINE_GAMEPLAY_TAG(DeadTag, "State.Dead")
}

void UGEHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(Health);
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(MaxHealth);
    GAMEPLAYATTRIBUTE_DOREPLIFETIME_CONDITION_NOTIFY(HealthRegenRate);
}

void UGEHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if(Attribute == GetHealthAttribute()) // 체력
    {
        // 사망 시 DeadTag 적용
        if(NewValue <= 0.f)
        {
            GetOwningAbilitySystemComponent()->AddLooseGameplayTag(GEGameplayTags::DeadTag);
        }
    }
}

void UGEHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;

    if(Attribute == GetDamageAttribute()) // 데미지
    {
        // 로컬 변수로 저장 후 Damage Attribute 값 초기화
        const float LocalDamage = GetDamage();
        SetDamage(0.f);

        // 데미지 처리
        TakeDamageByGameplayEffect(Data, LocalDamage);
    }
}

void UGEHealthAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
    Super::ClampAttributes(Attribute, NewValue);

    if(Attribute == GetHealthAttribute()) // 체력
    {
        // 0 <= 체력 <= 최대 체력
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
    else if(Attribute == GetMaxHealthAttribute()) // 최대 체력
    {
        // 0 <= 최대 체력
        NewValue = FMath::Max(NewValue, 0.f);
    }
}

void UGEHealthAttributeSet::AdjustAttributes(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::AdjustAttributes(Attribute, OldValue, NewValue);

    if(Attribute == GetMaxHealthAttribute()) // 최대 체력
    {
        // 체력 비율 유지
        AdjustAttributeForMaxChange(Health, MaxHealth, OldValue, NewValue, GetHealthAttribute());
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
