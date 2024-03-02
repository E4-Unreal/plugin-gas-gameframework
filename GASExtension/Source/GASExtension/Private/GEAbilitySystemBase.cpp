// Fill out your copyright notice in the Description page of Project Settings.

#include "GEAbilitySystemBase.h"

#include "FunctionLibraries/GEFunctionLibrary.h"

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

void UGEAbilitySystemBase::InitializeAttributes()
{
    // 기본 AttributeSet 생성 및 등록
    UGEFunctionLibrary::AddAttributeSets(DefaultAttributes, this);

    // 기본 GameplayEffect 적용
    UGEFunctionLibrary::ApplyGameplayEffectsToSystem(DefaultEffects, this);
}

void UGEAbilitySystemBase::GiveDefaultAbilities()
{
    // 기본 어빌리티 부여
    for (const TSubclassOf<UGameplayAbility> DefaultAbility : DefaultAbilities)
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
