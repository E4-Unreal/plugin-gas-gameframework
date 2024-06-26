// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFGameplayEventManager.h"

#include "AbilitySystemGlobals.h"
#include "GGFGameplayTags.h"
#include "AbilitySystem/GGFAbilitySystem.h"
#include "GameFramework/Character.h"

void UGGFGameplayEventAction::SetOwner(AActor* NewOwner)
{
    if(Owner.IsValid() || NewOwner == nullptr) return;

    Owner = NewOwner;
    bValid = true;
}

bool UGGFGameplayEventAction::IsValid() const
{
    return bValid && EventTag.MatchesTag(Event::Root);
}

void UGGFGameplayEventAction::ActivateAction_Implementation()
{
    UE_LOG(LogTemp, Error, TEXT("Acitvate"));

    Owner->Destroy();
}

void UGGFCharacterEventAction::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(AActor* OwnerActor = GetOwner())
    {
        OwnerCharacter = Cast<ACharacter>(OwnerActor);
        bValid = OwnerCharacter.IsValid();
    }
}

UGGFGameplayEventManager::UGGFGameplayEventManager()
{
    bWantsInitializeComponent = true;
    SetIsReplicatedByDefault(true);
}

void UGGFGameplayEventManager::InitializeComponent()
{
    Super::InitializeComponent();

    if(auto AbilitySystem = Cast<UGGFAbilitySystem>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner())))
    {
        // 멀티캐스트 게임플레이 이벤트 기능 활성화 및 바인딩
        AbilitySystem->bUseMulticastGameplayEvent = true;
        AbilitySystem->OnGameplayEventInvoked.AddDynamic(this, &ThisClass::HandleGameplayEvent);

        // GameplayEventAction 인스턴스 생성
        CreateGameplayEventActionInstances();

        bValid = true;
    }
}

void UGGFGameplayEventManager::CreateGameplayEventActionInstances()
{
    GameplayEventActionInstances.Reserve(GameplayEventActions.Num());
    for (TSubclassOf<UGGFGameplayEventAction> ActionClass : GameplayEventActions)
    {
        if(ActionClass)
        {
            // GameplayEventAction 인스턴스 생성
            UGGFGameplayEventAction* ActionInstance = NewObject<UGGFGameplayEventAction>(this, ActionClass);
            ActionInstance->EventTag = ActionClass->GetDefaultObject<UGGFGameplayEventAction>()->EventTag;
            ActionInstance->SetOwner(GetOwner());

            // 유효성 검사 (실패 시 GC에서 생성된 인스턴스 파괴)
            if(ActionInstance->IsNotValid()) continue;

            // GameplayEventAction 인스턴스 등록
            GameplayEventActionInstances.Emplace(ActionInstance);
        }
    }
}

void UGGFGameplayEventManager::HandleGameplayEvent(const FGameplayTag& EventTag)
{
    for (UGGFGameplayEventAction* ActionInstance : GameplayEventActionInstances)
    {
        if(ActionInstance->EventTag.MatchesTag(EventTag))
        {
            ActionInstance->ActivateAction();
        }
    }
}
