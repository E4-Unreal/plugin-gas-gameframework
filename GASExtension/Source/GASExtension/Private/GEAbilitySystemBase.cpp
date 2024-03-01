// Fill out your copyright notice in the Description page of Project Settings.

#include "GEAbilitySystemBase.h"

void UGEAbilitySystemBase::OnRegister()
{
    // InitFromMetaDataTable
    Super::OnRegister();

    // AttributeSet 초기화
    InitializeAttributes();
}

void UGEAbilitySystemBase::BeginPlay()
{
    Super::BeginPlay();

    // Startup GameplayEffect 적용
    ApplyEffects(StartupEffects);
}

void UGEAbilitySystemBase::InitializeAttributes()
{
    // 기본 AttributeSet 생성 및 등록
    CreateAttributes(DefaultAttributes);

    // 기본 GameplayEffect 적용
    ApplyEffects(DefaultEffects);
}

void UGEAbilitySystemBase::CreateAttributes(const TArray<TSubclassOf<UAttributeSet>>& AttributeClasses)
{
    for (const TSubclassOf<UAttributeSet> AttributeClass : AttributeClasses)
    {
        CreateAttribute(AttributeClass);
    }
}

void UGEAbilitySystemBase::CreateAttribute(const TSubclassOf<UAttributeSet> AttributeClass)
{
    // 유효성 검사
    if(AttributeClass == nullptr) return;

    // AttributeSet 생성 및 등록
    GetOrCreateAttributeSubobject(AttributeClass);
}

void UGEAbilitySystemBase::ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses)
{
    for (const TSubclassOf<UGameplayEffect> EffectClass : EffectClasses)
    {
        ApplyEffect(EffectClass);
    }
}

void UGEAbilitySystemBase::ApplyEffect(const TSubclassOf<UGameplayEffect> EffectClass)
{
    // 자기 자신에게 Gameplay Effect 적용
    const FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
    if(GameplayEffectSpecHandle.IsValid())
    {
        ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
    }
}
