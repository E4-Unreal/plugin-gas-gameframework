// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GEStateAbility.h"
#include "GECharacterStateAbility.generated.h"

/**
 * 캐릭터 상태 전용 어빌리티로 캐릭터 레퍼런스를 캐싱하고 있습니다
 */
UCLASS()
class GASEXTENSION_API UGECharacterStateAbility : public UGEStateAbility
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "GECharacterStateAbility")
    TWeakObjectPtr<ACharacter> AvatarCharacter;

protected:
    /* GameplayAbility */
    virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData) override;
};
