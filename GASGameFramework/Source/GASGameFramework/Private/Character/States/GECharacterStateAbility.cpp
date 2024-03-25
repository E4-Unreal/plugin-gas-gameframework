// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/GECharacterStateAbility.h"

#include "GameFramework/Character.h"

void UGECharacterStateAbility::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
    Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);

    // 캐릭터 레퍼런스 캐싱
    if(!AvatarCharacter.IsValid())
    {
        AvatarCharacter = Cast<ACharacter>(ActorInfo->AvatarActor);
    }
}
