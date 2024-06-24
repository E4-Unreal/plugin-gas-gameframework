// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GECharacterAbility.h"
#include "GGFGA_Montage.generated.h"

/**
 *
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFGA_Montage : public UGECharacterAbility
{
    GENERATED_BODY()

public:
    // 몽타주
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Animation")
    TObjectPtr<UAnimMontage> MontageToPlay;

    // 몽타주 재생 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Animation")
    float Duration = 2;

public:
    UGGFGA_Montage();

    /* GameplayAbility */

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;

protected:
    /* 이벤트 */

    UFUNCTION(BlueprintNativeEvent)
    void OnMontageCompleted();

    UFUNCTION(BlueprintNativeEvent)
    void OnMontageInterrupted();

    UFUNCTION(BlueprintNativeEvent)
    void OnPlayMontageNotifyBegin(FName NotifyName);

    UFUNCTION(BlueprintNativeEvent)
    void OnPlayMontageNotifyEnd(FName NotifyName);

    /* 메서드 */
    virtual void SetCharacterMovement(bool bEnable);
};
