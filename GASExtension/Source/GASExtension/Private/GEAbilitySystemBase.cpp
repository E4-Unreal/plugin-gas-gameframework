// Fill out your copyright notice in the Description page of Project Settings.

#include "GEAbilitySystemBase.h"

UGEAbilitySystemBase::UGEAbilitySystemBase()
{
    bWantsInitializeComponent = true;
}

void UGEAbilitySystemBase::InitializeComponent()
{
    Super::InitializeComponent();

    // 서버에서만 초기화 진행
    if(!IsOwnerActorAuthoritative()) return;

    // AttributeSet 설정 및 초기화
    InitializeAttributes();

    // 기본 Abilities 를 부여합니다.
    GiveDefaultAbilities();
}

void UGEAbilitySystemBase::BeginPlay()
{
    Super::BeginPlay();

    // 시작 GameplayEffect 적용
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
    const FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingSpec(EffectClass, 0, MakeEffectContext());
    if(GameplayEffectSpecHandle.IsValid())
    {
        ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
    }
}

void UGEAbilitySystemBase::GiveDefaultAbilities()
{
    // 패시브 어빌리티 부여
    for (const auto& DefaultPassiveAbility : DefaultPassiveAbilities)
    {
        // null 검사
        if(DefaultPassiveAbility == nullptr) continue;

        // GameplayAbilitySpec 생성
        FGameplayAbilitySpec AbilitySpec = BuildAbilitySpecFromClass(DefaultPassiveAbility);

        // 유효성 검사
        if (!IsValid(AbilitySpec.Ability)) return;

        // 어빌리티 1회 발동
        GiveAbilityAndActivateOnce(AbilitySpec);
    }

    // 일반 어빌리티 부여
    for (auto DefaultAbility : DefaultAbilities)
    {
        // null 검사
        if(DefaultAbility == nullptr) continue;

        // GameplayAbilitySpec 생성
        FGameplayAbilitySpec AbilitySpec = BuildAbilitySpecFromClass(DefaultAbility);

        // 유효성 검사
        if (!IsValid(AbilitySpec.Ability)) return;

        // 어빌리티 부여
        GiveAbility(AbilitySpec);
    }
}
