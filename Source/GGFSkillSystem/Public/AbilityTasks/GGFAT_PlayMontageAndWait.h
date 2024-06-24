// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GGFAT_PlayMontageAndWait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayMontageAnimNotifySignature, FName, NotifyName);

/**
 * AbilityTask_PlayMontageAndWait에서 PlayMontageAnimNotify 이벤트 바인딩이 추가된 버전입니다.
 */
UCLASS()
class GGFSKILLSYSTEM_API UGGFAT_PlayMontageAndWait : public UAbilityTask_PlayMontageAndWait
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FPlayMontageAnimNotifySignature OnPlayMontageNotifyBegin;

    UPROPERTY(BlueprintAssignable)
    FPlayMontageAnimNotifySignature OnPlayMontageNotifyEnd;

public:
    UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="PlayMontageAndWaitTask",
        HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static UGGFAT_PlayMontageAndWait* CreatePlayMontageAndWaitTask(UGameplayAbility* OwningAbility,
        FName TaskInstanceName, UAnimMontage* InMontageToPlay, float InRate = 1.f, FName InStartSection = NAME_None, bool InStopWhenAbilityEnds = true, float InAnimRootMotionTranslationScale = 1.f, float InStartTimeSeconds = 0.f, bool InAllowInterruptAfterBlendOut = false);

    virtual void Activate() override;

protected:
    UFUNCTION()
    void InternalOnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

    UFUNCTION()
    void InternalOnPlayMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
