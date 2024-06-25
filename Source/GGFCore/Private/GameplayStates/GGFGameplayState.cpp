// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStates/GGFGameplayState.h"

#include "GGFGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

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
