// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEAbilitySystem.h"

#include "GEBlueprintFunctionLibrary.h"
#include "GEGameplayTags.h"

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

int32 UGEAbilitySystem::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
    // 멀티캐스트 게임플레이 이벤트 사용 설정 및 서버 액터인지 확인
    if(bUseMulticastGameplayEvent && IsOwnerActorAuthoritative() && EventTag.MatchesTag(GEGameplayTags::Event::Root))
    {
        NetMulticast_HandleGameplayEvent(EventTag);
    }

    return Super::HandleGameplayEvent(EventTag, Payload);
}

void UGEAbilitySystem::ServerInitializeComponent_Implementation()
{
    InitializeAbilitySystem();
}

void UGEAbilitySystem::NetMulticast_HandleGameplayEvent_Implementation(FGameplayTag EventTag)
{
    OnGameplayEventInvoked.Broadcast(EventTag);
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
