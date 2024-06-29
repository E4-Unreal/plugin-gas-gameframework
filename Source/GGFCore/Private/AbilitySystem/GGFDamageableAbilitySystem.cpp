// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GGFDamageableAbilitySystem.h"

#include "GGFGameplayTags.h"
#include "Logging.h"
#include "Attributes/GGFHealthAttributes.h"

UGGFDamageableAbilitySystem::UGGFDamageableAbilitySystem()
{
    // 체력 어트리뷰트 추가
    Attributes.AddUnique(UGGFHealthAttributes::StaticClass());
}

bool UGGFDamageableAbilitySystem::IsDead() const
{
    return HasMatchingGameplayTag(State::Dead);
}

void UGGFDamageableAbilitySystem::LocalInitializeComponent_Implementation()
{
    Super::LocalInitializeComponent_Implementation();

    // 죽음 이벤트 바인딩
    OnDead.AddDynamic(this, &ThisClass::InternalOnDead);

    // 죽음 태그 이벤트 바인딩
    FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged = RegisterGameplayTagEvent(State::Dead, EGameplayTagEventType::NewOrRemoved);
    OnGameplayEffectTagCountChanged.AddUObject(this, &ThisClass::OnDeadTagAdded);
}

void UGGFDamageableAbilitySystem::ServerInitializeComponent_Implementation()
{
    Super::ServerInitializeComponent_Implementation();

    // 체력 값 변경 이벤트 등록
    RegisterHealthValueChangeEvent();

    // 체력 어트리뷰트 초기화
    FGGFAttributeContainer HealthAttributeContainer
    {
        UGGFHealthAttributes::GetHealthAttribute(),
        UGGFHealthAttributes::GetMaxHealthAttribute(),
        UGGFHealthAttributes::GetHealthRegenRateAttribute()
    };

    InitAttribute(HealthAttributeContainer, MaxHealth);
}

void UGGFDamageableAbilitySystem::InternalOnDead_Implementation()
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

    LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT(""))
#endif
}

void UGGFDamageableAbilitySystem::RegisterHealthValueChangeEvent()
{
    FOnGameplayAttributeValueChange& Delegate = GetGameplayAttributeValueChangeDelegate(UGGFHealthAttributes::GetHealthAttribute());
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

void UGGFDamageableAbilitySystem::OnDeadTagAdded(const FGameplayTag Tag, int32 Count)
{
    // 죽음 이벤트 호출
    if(Count == 1) OnDead.Broadcast();
}
