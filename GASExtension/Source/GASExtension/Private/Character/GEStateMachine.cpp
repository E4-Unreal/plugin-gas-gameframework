// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GEStateMachine.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Character/GEState.h"

UGEStateMachine::UGEStateMachine()
{
    bWantsInitializeComponent = true;
}

void UGEStateMachine::InitializeComponent()
{
    Super::InitializeComponent();

    AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
    if(AbilitySystem.IsValid())
    {
        // 게임플레이 태그 변화 이벤트 바인딩
        RegisterGameplayTagEvent();

        // 상태 초기화
        CreateStates();
    }
}

void UGEStateMachine::OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount)
{
    if(NewCount > 0)
    {
        // Enter
        for (const auto& State : States)
        {
            State->Enter(Tag);

            // 등록되지 않은 상태라면 활성화 성공 시 등록
            if(!ActivatedStates.Contains(State) && State->IsActivated())
                ActivatedStates.Add(State);
        }
    }
    else
    {
        // Exit
        for (int i = ActivatedStates.Num() - 1; i >= 0; i--)
        {
            ActivatedStates[i]->Exit(Tag);

            // 비활성화되었다면 등록 해제
            if(!ActivatedStates[i]->IsActivated())
                ActivatedStates.RemoveAt(i);
        }
    }
}

void UGEStateMachine::RegisterGameplayTagEvent()
{
    // 모든 트리거 태그 쿼리
    FGameplayTagContainer TagsToRegister;
    for (const auto& StateClass : StateClasses)
    {
        if(StateClass == nullptr) continue;
        TagsToRegister.AppendTags(StateClass->GetDefaultObject<UGEState>()->GetTriggers());
    }

    // 트리거 태그 이벤트 등록
    for (const auto& Tag : TagsToRegister)
    {
        FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged = AbilitySystem->RegisterGameplayTagEvent(Tag);
        OnGameplayEffectTagCountChanged.AddUObject(this, &ThisClass::OnGameplayEffectTagCountChanged_Event);
    }
}

void UGEStateMachine::CreateStates()
{
    for (const auto& StateClass : StateClasses)
    {
        if(StateClass == nullptr) continue;
        const auto& State = NewObject<UGEState>(this, StateClass);
        State->Init(this);
        States.Add(State);
    }
}
