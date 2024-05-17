// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GEGameplayEventManager.h"

#include "AbilitySystemGlobals.h"
#include "GEGameplayTags.h"
#include "AbilitySystem/GEAbilitySystem.h"
#include "GameFramework/Character.h"

void UGEGameplayEventAction::SetOwner(AActor* NewOwner)
{
    if(Owner.IsValid() || NewOwner == nullptr) return;

    Owner = NewOwner;
    bValid = true;
}

bool UGEGameplayEventAction::IsValid() const
{
    return bValid && EventTag.MatchesTag(GEGameplayTags::Event::Root);
}

void UGEGameplayEventAction::ActivateAction_Implementation()
{
    UE_LOG(LogTemp, Error, TEXT("Acitvate"));

    Owner->Destroy();
}

void UGECharacterEventAction::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if(AActor* OwnerActor = GetOwner())
    {
        OwnerCharacter = Cast<ACharacter>(OwnerActor);
        bValid = OwnerCharacter.IsValid();
    }
}

UGEGameplayEventManager::UGEGameplayEventManager()
{
    bWantsInitializeComponent = true;
    SetIsReplicatedByDefault(true);
}

void UGEGameplayEventManager::InitializeComponent()
{
    Super::InitializeComponent();

    if(UGEAbilitySystem* AbilitySystem = Cast<UGEAbilitySystem>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner())))
    {
        // 멀티캐스트 게임플레이 이벤트 기능 활성화 및 바인딩
        AbilitySystem->bUseMulticastGameplayEvent = true;
        AbilitySystem->OnGameplayEventInvoked.AddDynamic(this, &ThisClass::HandleGameplayEvent);

        // GameplayEventAction 인스턴스 생성
        CreateGameplayEventActionInstances();

        bValid = true;
    }
}

void UGEGameplayEventManager::CreateGameplayEventActionInstances()
{
    GameplayEventActionInstances.Reserve(GameplayEventActions.Num());
    for (TSubclassOf<UGEGameplayEventAction> ActionClass : GameplayEventActions)
    {
        if(ActionClass)
        {
            // GameplayEventAction 인스턴스 생성
            UGEGameplayEventAction* ActionInstance = NewObject<UGEGameplayEventAction>(this, ActionClass);
            ActionInstance->EventTag = ActionClass->GetDefaultObject<UGEGameplayEventAction>()->EventTag;
            ActionInstance->SetOwner(GetOwner());

            // 유효성 검사 (실패 시 GC에서 생성된 인스턴스 파괴)
            if(ActionInstance->IsNotValid()) continue;

            // GameplayEventAction 인스턴스 등록
            GameplayEventActionInstances.Emplace(ActionInstance);
        }
    }
}

void UGEGameplayEventManager::HandleGameplayEvent(const FGameplayTag& EventTag)
{
    for (UGEGameplayEventAction* ActionInstance : GameplayEventActionInstances)
    {
        if(ActionInstance->EventTag.MatchesTag(EventTag))
        {
            ActionInstance->ActivateAction();
        }
    }
}
