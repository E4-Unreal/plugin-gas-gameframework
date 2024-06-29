// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFGameplayStateMachine.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GameplayStates/GGFGameplayState.h"

UGGFGameplayStateMachine::UGGFGameplayStateMachine()
{
    bWantsInitializeComponent = true;
    PrimaryComponentTick.bCanEverTick = true;
}

void UGGFGameplayStateMachine::InitializeComponent()
{
    Super::InitializeComponent();

    if(UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
    {
        // GameplayEventAction 인스턴스 생성
        CreateGameplayStateInstances();

        bValid = true;
    }
}

void UGGFGameplayStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    for (auto StateInstance : StateInstances)
    {
        StateInstance->Tick(DeltaTime);
    }
}

void UGGFGameplayStateMachine::CreateGameplayStateInstances()
{
    StateInstances.Reserve(StateClasses.Num());
    for (TSubclassOf<UGGFGameplayState> StateClass : StateClasses)
    {
        // 유혀성 검사
        if(StateClass)
        {
            // GameplayState 인스턴스 생성
            UGGFGameplayState* StateInstance = NewObject<UGGFGameplayState>(this, StateClass);
            StateInstance->StateTag = StateClass->GetDefaultObject<UGGFGameplayState>()->StateTag;
            StateInstance->SetOwner(GetOwner());

            // 유효성 검사 (실패 시 GC에서 생성된 인스턴스 파괴)
            if(StateInstance->IsNotValid()) continue;

            // GameplayState 인스턴스 등록
            StateInstances.Emplace(StateInstance);

            // 게임플레이 태그 부착 이벤트 바인딩
            UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
            FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged =
                AbilitySystem->RegisterGameplayTagEvent(StateInstance->StateTag, EGameplayTagEventType::NewOrRemoved);
            OnGameplayEffectTagCountChanged.AddUObject(StateInstance, &UGGFGameplayState::OnGameplayEffectTagCountChanged);
        }
    }
}
