// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEAbilitySystem.h"

#include "GEBlueprintFunctionLibrary.h"
#include "GEGameplayTags.h"
#include "Attributes/GEAttributeSetBase.h"

UGEAbilitySystem::UGEAbilitySystem()
{
    bWantsInitializeComponent = true;
}

void UGEAbilitySystem::InitializeComponent()
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

int32 UGEAbilitySystem::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
    // 멀티캐스트 게임플레이 이벤트 사용 설정 및 서버 액터인지 확인
    if(bUseMulticastGameplayEvent && IsOwnerActorAuthoritative() && EventTag.MatchesTag(GEGameplayTags::Event::Root))
    {
        NetMulticast_HandleGameplayEvent(EventTag);
    }

    return Super::HandleGameplayEvent(EventTag, Payload);
}

void UGEAbilitySystem::InitAttribute(const FGEAttributeContainer& AttributeContainer, float MaxValue, float Ratio,
    float RegenRate)
{
    MaxValue = FMath::Max(MaxValue, 0);
    Ratio = FMath::Clamp(Ratio, 0, 1);
    RegenRate = FMath::Max(RegenRate, 0);

    SetNumericAttributeBase(AttributeContainer.MaxAttribute, MaxValue);
    SetNumericAttributeBase(AttributeContainer.Attribute, MaxValue * Ratio);
    SetNumericAttributeBase(AttributeContainer.AttributeRegenRate, RegenRate);
}

void UGEAbilitySystem::ServerInitializeComponent_Implementation()
{
    // 기본 AttributeSet 생성 및 등록
    UGEBlueprintFunctionLibrary::AddAttributeSetsToSystem(Attributes, this);

    // TODO 리팩토링
    // 기본 Stats 생성 및 등록
    TArray<TSubclassOf<UAttributeSet>> CastedStats;
    CastedStats.Reserve(Stats.Num());
    for (auto StatClass : Stats)
    {
        CastedStats.Emplace(StatClass);
    }
    UGEBlueprintFunctionLibrary::AddAttributeSetsToSystem(CastedStats, this);

    // 기본 GameplayEffect 적용
    UGEBlueprintFunctionLibrary::ApplyGameplayEffectsToSystem(Effects, this);

    // 기본 GameplayAbility 부여
    UGEBlueprintFunctionLibrary::GiveAbilitiesToSystem(Abilities, this);
}

void UGEAbilitySystem::LocalInitializeComponent_Implementation()
{
    // 기본 게임플레이 태그 부여
    AddLooseGameplayTags(GameplayTags);
}

void UGEAbilitySystem::NetMulticast_HandleGameplayEvent_Implementation(FGameplayTag EventTag)
{
    OnGameplayEventInvoked.Broadcast(EventTag);
}
