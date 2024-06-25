// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFGameplayStateMachine.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GGFGameplayTags.h"
#include "GameFramework/Character.h"

void UGGFGameplayState::SetOwner(AActor* NewOwner)
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

bool UGGFGameplayState::IsValid() const
{
    return bValid && StateTag.MatchesTag(State::Root);
}

void UGGFGameplayState::Enter()
{
    // 이미 활성화된 상태인지 검사
    if(bActivated) return;
    bActivated = true;

    OnEnter();
}

void UGGFGameplayState::Tick(float DeltaTime)
{
    // 활성화된 상태인지 검사
    if(!bActivated) return;

    OnTick(DeltaTime);
}

void UGGFGameplayState::Exit()
{
    // 활성화된 상태인지 검사
    if(!bActivated) return;
    bActivated = false;

    OnExit();
}

void UGGFGameplayState::OnEnter_Implementation()
{

}

void UGGFGameplayState::OnTick_Implementation(float DeltaTime)
{

}

void UGGFGameplayState::OnExit_Implementation()
{

}

void UGGFGameplayState::OnGameplayEffectTagCountChanged(const FGameplayTag Tag, int32 Count)
{
    // 태그 검사
    if(!StateTag.MatchesTag(Tag)) return;

    if(Count > 0)
        Enter();
    else
        Exit();
}

void UGGFCharacterState::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(AActor* OwnerActor = GetOwner())
    {
        OwnerCharacter = Cast<ACharacter>(OwnerActor);
        bValid = OwnerCharacter.IsValid();
    }
}

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
