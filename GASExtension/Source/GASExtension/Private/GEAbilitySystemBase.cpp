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
    InitializeAbilitySystem();
}

void UGEAbilitySystemBase::InitializeAbilitySystem()
{
    // 기본 AttributeSet 생성 및 등록
    UGEFunctionLibrary::AddAttributeSetsToSystem(DefaultAttributes, this);

    // 기본 GameplayEffect 적용
    UGEFunctionLibrary::ApplyGameplayEffectsToSystem(DefaultEffects, this);

    // 기본 GameplayAbility 부여
    UGEFunctionLibrary::GiveAbilitiesToSystem(DefaultAbilities, this);
}
