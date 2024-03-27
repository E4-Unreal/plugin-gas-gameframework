// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SetCameraFOV.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetCameraFOVDelegate);

class UCameraComponent;

/**
 * 카메라 FOV를 조정을 위한 어빌리티 태스크로 ADS에서 사용하기 위해 작성되었습니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UAbilityTask_SetCameraFOV : public UAbilityTask
{
    GENERATED_BODY()

    float TargetFOV;
    float InterpSpeed;
    TWeakObjectPtr<UCameraComponent> Camera;

public:
    UPROPERTY(BlueprintAssignable)
    FSetCameraFOVDelegate OnEnd;

public:
    UAbilityTask_SetCameraFOV();

    UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", DisplayName="Set Camera FOV"), Category="Ability|Tasks")
    static UAbilityTask_SetCameraFOV* SetCameraFOV(UGameplayAbility* OwningAbility, float TargetFOV, float InInterpSpeed = 15.f);

    virtual void Activate() override;
    virtual void TickTask(float DeltaTime) override;
};
