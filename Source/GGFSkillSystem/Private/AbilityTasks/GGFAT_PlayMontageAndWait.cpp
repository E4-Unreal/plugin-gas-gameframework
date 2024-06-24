// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/GGFAT_PlayMontageAndWait.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemLog.h"
#include "GameFramework/Character.h"


UGGFAT_PlayMontageAndWait* UGGFAT_PlayMontageAndWait::CreatePlayMontageAndWaitTask(UGameplayAbility* OwningAbility,
    FName TaskInstanceName, UAnimMontage* InMontageToPlay, float InRate, FName InStartSection,
    bool InStopWhenAbilityEnds, float InAnimRootMotionTranslationScale, float InStartTimeSeconds,
    bool InAllowInterruptAfterBlendOut)
{
    UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(InRate);

    UGGFAT_PlayMontageAndWait* NewTask = NewAbilityTask<UGGFAT_PlayMontageAndWait>(OwningAbility, TaskInstanceName);
    NewTask->MontageToPlay = InMontageToPlay;
    NewTask->Rate = InRate;
    NewTask->StartSection = InStartSection;
    NewTask->AnimRootMotionTranslationScale = InAnimRootMotionTranslationScale;
    NewTask->bStopWhenAbilityEnds = InStopWhenAbilityEnds;
    NewTask->bAllowInterruptAfterBlendOut = InAllowInterruptAfterBlendOut;
    NewTask->StartTimeSeconds = InStartTimeSeconds;

    return NewTask;
}

void UGGFAT_PlayMontageAndWait::Activate()
{
    if (Ability == nullptr)
	{
		return;
	}

	bool bPlayedMontage = false;

	if (UAbilitySystemComponent* ASC = AbilitySystemComponent.Get())
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			if (ASC->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection, StartTimeSeconds) > 0.f)
			{
				// Playing a montage could potentially fire off a callback into game code which could kill this ability! Early out if we are  pending kill.
				if (ShouldBroadcastAbilityTaskDelegates() == false)
				{
					return;
				}

				InterruptedHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UAbilityTask_PlayMontageAndWait::OnGameplayAbilityCancelled);

				BlendingOutDelegate.BindUObject(this, &UAbilityTask_PlayMontageAndWait::OnMontageBlendingOut);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

				MontageEndedDelegate.BindUObject(this, &UAbilityTask_PlayMontageAndWait::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

			    // 애님 몽타주 노티파이 이벤트 바인딩
			    AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::InternalOnPlayMontageNotifyBegin);
			    AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &ThisClass::InternalOnPlayMontageNotifyEnd);

				ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
				if (Character && (Character->GetLocalRole() == ROLE_Authority ||
								  (Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
				{
					Character->SetAnimRootMotionTranslationScale(AnimRootMotionTranslationScale);
				}

				bPlayedMontage = true;
			}
		}
		else
		{
			ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWait call to PlayMontage failed!"));
		}
	}
	else
	{
		ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWait called on invalid AbilitySystemComponent"));
	}

	if (!bPlayedMontage)
	{
		ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWait called in Ability %s failed to play montage %s; Task Instance Name %s."), *Ability->GetName(), *GetNameSafe(MontageToPlay),*InstanceName.ToString());
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast();
		}
	}

	SetWaitingOnAvatar();
}

void UGGFAT_PlayMontageAndWait::InternalOnPlayMontageNotifyBegin(FName NotifyName,
    const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    OnPlayMontageNotifyBegin.Broadcast(NotifyName);
}

void UGGFAT_PlayMontageAndWait::InternalOnPlayMontageNotifyEnd(FName NotifyName,
    const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    OnPlayMontageNotifyEnd.Broadcast(NotifyName);
}
