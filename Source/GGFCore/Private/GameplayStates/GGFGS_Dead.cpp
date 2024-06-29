// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayStates/GGFGS_Dead.h"

#include "AbilitySystemComponent.h"
#include "GGFGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/GGFGameModeInterface.h"

UGGFGS_Dead::UGGFGS_Dead()
{
    StateTag = State::Dead;
}

void UGGFGS_Dead::OnEnter_Implementation()
{
    Super::OnEnter_Implementation();

    // 타이머 활성화
    auto& TimerManager = GetOwner()->GetWorldTimerManager();
    TimerManager.SetTimer(DelayTimer, this, &ThisClass::OnDelayTimerFinished, DelayTime);

    // 모든 어빌리티 입력 비활성화
    for (auto& ActivatableAbility : GetOwnerAbilitySystem()->GetActivatableAbilities())
    {
        ActivatableAbility.InputPressed = false;
    }

    // 캐릭터 콜리전 비활성화
    if(auto Character = Cast<ACharacter>(GetOwnerPawn()))
    {
        Character->GetMesh()->SetCollisionProfileName("Ragdoll");
        Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
}

void UGGFGS_Dead::OnExit_Implementation()
{
    // 타이머 비활성화
    auto& TimerManager = GetOwner()->GetWorldTimerManager();
    if(TimerManager.IsTimerActive(DelayTimer)) TimerManager.ClearTimer(DelayTimer);

    // 캐릭터 콜리전 활성화
    if(auto Character = Cast<ACharacter>(GetOwnerPawn()))
    {
        Character->GetMesh()->SetCollisionProfileName("CharacterMesh");
        Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }

    Super::OnExit_Implementation();
}

void UGGFGS_Dead::OnDelayTimerFinished_Implementation()
{
    // 유효성 검사
    if(GetOwnerPawn() == nullptr) return;

    // 서버 전용
    if(auto GameMode = GetWorld()->GetAuthGameMode())
    {
        // 관전 모드 설정
        if(auto PlayerState = GetOwnerPawn()->GetPlayerState())
        {
            PlayerState->SetIsSpectator(true);
        }

        // 관전 상대 변경
        if(GameMode->Implements<UGGFGameModeInterface>())
        {
            IGGFGameModeInterface::Execute_SetViewTargetToNextPlayer(GameMode, Cast<APlayerController>(GetOwnerPawn()->Controller));
        }

        // 파괴
        GetOwnerPawn()->Destroy();
    }
}
