// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEAbilitySystem.h"

#include "GEBlueprintFunctionLibrary.h"

UGEAbilitySystem::UGEAbilitySystem()
{
    bWantsInitializeComponent = true;
}

void UGEAbilitySystem::InitializeComponent()
{
    Super::InitializeComponent();

    // 서버 전용 컴포넌트 초기화
    if(IsOwnerActorAuthoritative())
    {
        ServerInitializeComponent();
    }
}

void UGEAbilitySystem::ServerInitializeComponent_Implementation()
{
    InitializeAbilitySystem();
}

void UGEAbilitySystem::InitializeAbilitySystem()
{
    // 기본 AttributeSet 생성 및 등록
    UGEBlueprintFunctionLibrary::AddAttributeSetsToSystem(DefaultAttributes, this);

    // 기본 Stats 생성 및 등록
    UGEBlueprintFunctionLibrary::AddAttributeSetsToSystem(DefaultStats, this);

    // 기본 GameplayEffect 적용
    UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(DefaultEffects, this);

    // 기본 GameplayAbility 부여
    UGEBlueprintFunctionLibrary::GiveAbilitiesToSystem(DefaultAbilities, this);
}
