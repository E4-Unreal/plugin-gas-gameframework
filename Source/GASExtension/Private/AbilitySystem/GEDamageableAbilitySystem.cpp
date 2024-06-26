﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEDamageableAbilitySystem.h"

#include "GEGameplayTags.h"
#include "Logging.h"
#include "Attributes/GEHealthAttributes.h"

using namespace GEGameplayTags;

UGEDamageableAbilitySystem::UGEDamageableAbilitySystem()
{
    // 체력 어트리뷰트 추가
    Attributes.AddUnique(UGEHealthAttributes::StaticClass());
}

bool UGEDamageableAbilitySystem::IsDead() const
{
    return HasMatchingGameplayTag(State::Dead);
}

void UGEDamageableAbilitySystem::LocalInitializeComponent_Implementation()
{
    Super::LocalInitializeComponent_Implementation();

    // 죽음 이벤트 바인딩
    OnDead.AddDynamic(this, &ThisClass::InternalOnDead);

    // 죽음 태그 이벤트 바인딩
    FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged = RegisterGameplayTagEvent(State::Dead, EGameplayTagEventType::NewOrRemoved);
    OnGameplayEffectTagCountChanged.AddUObject(this, &ThisClass::OnDeadTagAdded);
}

void UGEDamageableAbilitySystem::ServerInitializeComponent_Implementation()
{
    Super::ServerInitializeComponent_Implementation();

    // 체력 값 변경 이벤트 등록
    RegisterHealthValueChangeEvent();

    // 체력 어트리뷰트 초기화
    FGEAttributeContainer HealthAttributeContainer
    {
        UGEHealthAttributes::GetHealthAttribute(),
        UGEHealthAttributes::GetMaxHealthAttribute(),
        UGEHealthAttributes::GetHealthRegenRateAttribute()
    };

    InitAttribute(HealthAttributeContainer, MaxHealth);
}

void UGEDamageableAbilitySystem::InternalOnDead_Implementation()
{
#if WITH_EDITOR
    FString Role = "None";
    switch (GetOwnerRole())
    {
    case ROLE_Authority:
        Role = "Authority";
        break;
    case ROLE_AutonomousProxy:
        Role = "AutonomousProxy";
        break;
    case ROLE_SimulatedProxy:
        Role = "SimulatedProxy";
        break;
    default:
        Role = "None";
    break;
    }
    UE_LOG(LogGASExtension, Log, TEXT("%s > %s > %s::%s"),*Role, *GetOwner()->GetName(), *StaticClass()->GetName(), *FString(__func__))
#endif
}

void UGEDamageableAbilitySystem::RegisterHealthValueChangeEvent()
{
    FOnGameplayAttributeValueChange& Delegate = GetGameplayAttributeValueChangeDelegate(UGEHealthAttributes::GetHealthAttribute());
    Delegate.AddLambda([this](const FOnAttributeChangeData& OnAttributeChangeData)
    {
        // 중복 호출 방지 및 죽음 판정
        if(!IsDead() && FMath::IsNearlyZero(OnAttributeChangeData.NewValue))
        {
            // 서버 태그 부착
            AddLooseGameplayTag(State::Dead);

            // 클라이언트 태그 부착
            AddReplicatedLooseGameplayTag(State::Dead);
        }
    });
}

void UGEDamageableAbilitySystem::OnDeadTagAdded(const FGameplayTag Tag, int32 Count)
{
    // 죽음 이벤트 호출
    if(Count == 1) OnDead.Broadcast();
}
