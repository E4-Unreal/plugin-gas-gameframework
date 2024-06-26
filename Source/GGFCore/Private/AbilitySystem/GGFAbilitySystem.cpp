﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GGFAbilitySystem.h"

#include "GGFGameplayTags.h"
#include "GGFBlueprintFunctionLibrary.h"

UGGFAbilitySystem::UGGFAbilitySystem()
{
    bWantsInitializeComponent = true;
}

void UGGFAbilitySystem::InitializeComponent()
{
    Super::InitializeComponent();

    // 서버, 클라이언트 공통 초기화 메서드
    LocalInitializeComponent();

    // 서버 전용 초기화 메서드
    if(IsOwnerActorAuthoritative())
    {
        ServerInitializeComponent();
    }
}

int32 UGGFAbilitySystem::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
    // 멀티캐스트 게임플레이 이벤트 사용 설정 및 서버 액터인지 확인
    if(bUseMulticastGameplayEvent && IsOwnerActorAuthoritative() && EventTag.MatchesTag(Event::Root))
    {
        NetMulticast_HandleGameplayEvent(EventTag);
    }

    return Super::HandleGameplayEvent(EventTag, Payload);
}

void UGGFAbilitySystem::InitAttribute(const FGGFAttributeContainer& AttributeContainer, float MaxValue, float Ratio,
    float RegenRate)
{
    MaxValue = FMath::Max(MaxValue, 0);
    Ratio = FMath::Clamp(Ratio, 0, 1);
    RegenRate = FMath::Max(RegenRate, 0);

    SetNumericAttributeBase(AttributeContainer.MaxAttribute, MaxValue);
    SetNumericAttributeBase(AttributeContainer.Attribute, MaxValue * Ratio);
    SetNumericAttributeBase(AttributeContainer.AttributeRegenRate, RegenRate);
}

void UGGFAbilitySystem::OnAbilitySpecDirtied(const FGameplayAbilitySpec& AbilitySpec)
{
}

void UGGFAbilitySystem::ServerInitializeComponent_Implementation()
{
    // 이벤트 바인딩
    AbilitySpecDirtiedCallbacks.AddUObject(this, &UGGFAbilitySystem::OnAbilitySpecDirtied);

    // 기본 AttributeSet 생성 및 등록
    UGGFBlueprintFunctionLibrary::AddAttributeSetsToSystem(Attributes, this);

    // TODO 리팩토링
    // 기본 Stats 생성 및 등록
    TArray<TSubclassOf<UAttributeSet>> CastedStats;
    CastedStats.Reserve(Stats.Num());
    for (auto StatClass : Stats)
    {
        CastedStats.Emplace(StatClass);
    }
    UGGFBlueprintFunctionLibrary::AddAttributeSetsToSystem(CastedStats, this);

    // 기본 GameplayEffect 적용
    UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToSelf(GetOwner(), Effects);

    // 기본 GameplayAbility 부여
    UGGFBlueprintFunctionLibrary::GiveAbilitiesToSystem(Abilities, this);
}

void UGGFAbilitySystem::LocalInitializeComponent_Implementation()
{
    // 기본 게임플레이 태그 부여
    AddLooseGameplayTags(GameplayTags);
}

void UGGFAbilitySystem::NetMulticast_HandleGameplayEvent_Implementation(FGameplayTag EventTag)
{
    OnGameplayEventInvoked.Broadcast(EventTag);
}