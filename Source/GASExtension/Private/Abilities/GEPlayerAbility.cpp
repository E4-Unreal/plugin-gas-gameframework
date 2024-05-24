// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GEPlayerAbility.h"

UGEPlayerAbility::UGEPlayerAbility()
{
    // 입력 리플리케이트
    bReplicateInputDirectly = true;
}

void UGEPlayerAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputReleased(Handle, ActorInfo, ActivationInfo);

    // 어빌리티 입력이 비활성화되면 어빌리티를 종료합니다.
    if(bIsActive) EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGEPlayerAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    // Input Release 외의 조건으로 인해 어빌리티가 종료되는 경우 Input Release 상태로 자동 변경
    GetCurrentAbilitySpec()->InputPressed = false;
}
