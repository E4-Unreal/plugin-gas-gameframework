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
    return bValid && StateTag.MatchesTag(State::Root);
}

void UGEGameplayState::Enter()
{
    // 이미 활성화된 상태인지 검사
    if(bActivated) return;
    bActivated = true;

    OnEnter();
}

void UGEGameplayState::Tick(float DeltaTime)
{
    // 활성화된 상태인지 검사
    if(!bActivated) return;

    OnTick(DeltaTime);
}

void UGEGameplayState::Exit()
{
    // 활성화된 상태인지 검사
    if(!bActivated) return;
    bActivated = false;

    OnExit();
}

void UGEGameplayState::OnEnter_Implementation()
{

}

void UGEGameplayState::OnTick_Implementation(float DeltaTime)
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
    PrimaryComponentTick.bCanEverTick = true;
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

void UGEGameplayStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    for (auto StateInstance : StateInstances)
    {
        StateInstance->Tick(DeltaTime);
    }
}

void UGEGameplayStateMachine::CreateGameplayStateInstances()
{
    StateInstances.Reserve(StateClasses.Num());
    for (TSubclassOf<UGEGameplayState> StateClass : StateClasses)
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
            StateInstances.Emplace(StateInstance);

            // 게임플레이 태그 부착 이벤트 바인딩
            UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
            FOnGameplayEffectTagCountChanged& OnGameplayEffectTagCountChanged =
                AbilitySystem->RegisterGameplayTagEvent(StateInstance->StateTag, EGameplayTagEventType::NewOrRemoved);
            OnGameplayEffectTagCountChanged.AddUObject(StateInstance, &UGEGameplayState::OnGameplayEffectTagCountChanged);
        }
    }
}
