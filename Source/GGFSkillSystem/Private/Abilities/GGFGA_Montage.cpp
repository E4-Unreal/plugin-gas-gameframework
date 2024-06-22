// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_Montage.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilityTasks/GGFAT_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Logging.h"
#include "GGFCharacterGameplayTags.h"

using namespace GGFGameplayTags;

UGGFGA_Montage::UGGFGA_Montage()
{
    bCancelableByInputRelease = false;

    // 태그 설정
    ActivationBlockedTags.AddTagFast(State::Falling);
}

void UGGFGA_Montage::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // 캐릭터 움직임 입력 비활성화
    SetCharacterMovement(false);

    // 몽타주 재생 어빌리티 태스크 생성
    float PlayRate = MontageToPlay->GetPlayLength() / Duration;
    auto PlayMontageAndWaitTask = UGGFAT_PlayMontageAndWait::CreatePlayMontageAndWaitTask(this, FName(MontageToPlay->GetName()), MontageToPlay, PlayRate);
    PlayMontageAndWaitTask->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);
    PlayMontageAndWaitTask->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCompleted);
    PlayMontageAndWaitTask->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnPlayMontageNotifyBegin);
    PlayMontageAndWaitTask->OnPlayMontageNotifyEnd.AddDynamic(this, &ThisClass::OnPlayMontageNotifyEnd);
    PlayMontageAndWaitTask->ReadyForActivation();
}

void UGGFGA_Montage::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // 캐릭터 움직임 입력 활성화
    SetCharacterMovement(true);
}

bool UGGFGA_Montage::InternalCanActivate()
{
    return Super::InternalCanActivate() && MontageToPlay;
}

void UGGFGA_Montage::OnMontageCompleted_Implementation()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGGFGA_Montage::OnMontageInterrupted_Implementation()
{
    CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UGGFGA_Montage::OnPlayMontageNotifyBegin_Implementation(FName NotifyName)
{
#if WITH_EDITOR
    LOG(Log, TEXT("%s"), *NotifyName.ToString())
#endif
}

void UGGFGA_Montage::OnPlayMontageNotifyEnd_Implementation(FName NotifyName)
{
#if WITH_EDITOR
    LOG(Log, TEXT("%s"), *NotifyName.ToString())
#endif
}

void UGGFGA_Montage::SetCharacterMovement(bool bEnable)
{
    auto Character = GetAvatarCharacter();
    auto PlayerController = Cast<APlayerController>(Character->Controller);
    auto CharacterMovement = GetAvatarCharacter()->GetCharacterMovement();

    if(bEnable)
    {
        if(PlayerController) Character->EnableInput(PlayerController);
        CharacterMovement->SetDefaultMovementMode();
    }
    else
    {
        if(PlayerController) Character->DisableInput(PlayerController);
        CharacterMovement->DisableMovement();
        CharacterMovement->StopMovementImmediately();
    }
}
