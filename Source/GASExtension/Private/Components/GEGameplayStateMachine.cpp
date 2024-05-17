// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GEGameplayStateMachine.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GEGameplayTags.h"
#include "GameFramework/Character.h"

void UGEGameplayState::SetOwner(AActor* NewOwner)
{
    // 중복 호출 방지
    if(Owner.IsValid()) return;

    // 입력 유효성 검사
    UAbilitySystemComponent* NewOwnerAbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(NewOwner);
    if(NewOwnerAbilitySystem == nullptr) return;

    // 할당
    Owner = NewOwner;
    OwnerAbilitySystem = NewOwnerAbilitySystem;
    bValid = true;
}

bool UGEGameplayState::IsValid() const
{
    return bValid && StateTag.MatchesTag(GEGameplayTags::State::State);
}

void UGEGameplayState::Enter()
{
    // 이미 활성화된 상태인지 검사
    if(bActivated) return;

    OnEnter();
}

void UGEGameplayState::Exit()
{
    // 활성화된 상태인지 검사
    if(!bActivated) return;

    OnExit();
}

void UGEGameplayState::OnEnter_Implementation()
{

}

void UGEGameplayState::OnExit_Implementation()
{

}

void UGEGameplayState::OnGameplayEffectTagCountChanged(const FGameplayTag Tag, int32 Count)
{
    // 태그 검사
    if(!StateTag.MatchesTag(Tag)) return;

    if(Count > 0)
        Enter();
    else
        Exit();
}

void UGECharacterState::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(AActor* OwnerActor = GetOwner())
    {
        OwnerCharacter = Cast<ACharacter>(OwnerActor);
        bValid = OwnerCharacter.IsValid();
    }
}

UGEGameplayStateMachine::UGEGameplayStateMachine()
{
    bWantsInitializeComponent = true;
}

void UGEGameplayStateMachine::InitializeComponent()
{
    Super::InitializeComponent();

    if(UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
    {
        // GameplayEventAction 인스턴스 생성
        CreateGameplayStateInstances();

        bValid = true;
    }
}

void UGEGameplayStateMachine::CreateGameplayStateInstances()
{
    GameplayStateInstances.Reserve(GameplayStates.Num());
    for (TSubclassOf<UGEGameplayState> StateClass : GameplayStates)
    {
        // 유혀성 검사
        if(StateClass)
        {
            // GameplayState 인스턴스 생성
            UGEGameplayState* StateInstance = NewObject<UGEGameplayState>(this, StateClass);
            StateInstance->StateTag = StateClass->GetDefaultObject<UGEGameplayState>()->StateTag;
            StateInstance->SetOwner(GetOwner());

            // 유효성 검사 (실패 시 GC에서 생성된 인스턴스 파괴)
            if(StateInstance->IsNotValid()) continue;

            // GameplayState 인스턴스 등록
            GameplayStateInstances.Emplace(StateInstance);

            // 게임플레이 태그 부착 이벤트 바인딩
            UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
            FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged =
                AbilitySystem->RegisterGameplayTagEvent(StateInstance->StateTag, EGameplayTagEventType::NewOrRemoved);
            OnGameplayEffectTagCountChanged.AddUObject(StateInstance, &UGEGameplayState::OnGameplayEffectTagCountChanged);
        }
    }
}
