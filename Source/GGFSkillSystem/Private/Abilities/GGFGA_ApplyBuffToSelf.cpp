// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_ApplyBuffToSelf.h"

#include "AbilitySystemComponent.h"

void UGGFGA_ApplyBuffToSelf::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
    Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);

    // 초기화
    bApplied = false;
}

void UGGFGA_ApplyBuffToSelf::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if(bApplyImmediately) ApplyBuffToSelf();
}

void UGGFGA_ApplyBuffToSelf::OnPlayMontageNotifyBegin_Implementation(FName NotifyName)
{
    Super::OnPlayMontageNotifyBegin_Implementation(NotifyName);

    ApplyBuffToSelf();
}

void UGGFGA_ApplyBuffToSelf::OnMontageCompleted_Implementation()
{
    Super::OnMontageCompleted_Implementation();

    ApplyBuffToSelf();
}

bool UGGFGA_ApplyBuffToSelf::InternalCanActivate()
{
    return Super::InternalCanActivate() && BuffClass;
}

void UGGFGA_ApplyBuffToSelf::ApplyBuffToSelf()
{
    if(bApplied) return;
    bApplied = true;

    auto AbilitySystem = GetAbilitySystemComponentFromActorInfo();
    AbilitySystem->ApplyGameplayEffectToSelf(BuffClass->GetDefaultObject<UGameplayEffect>(), GetAbilityLevel(), AbilitySystem->MakeEffectContext());
}
