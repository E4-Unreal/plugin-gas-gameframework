// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityTask_SetCameraFOV.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"

UAbilityTask_SetCameraFOV::UAbilityTask_SetCameraFOV()
{
    // 부드러운 FOV 전환을 위해 틱을 사용합니다.
    bTickingTask = true;
}

UAbilityTask_SetCameraFOV* UAbilityTask_SetCameraFOV::SetCameraFOV(UGameplayAbility* OwningAbility, float InTargetFOV, float InInterpSpeed)
{
    UAbilityTask_SetCameraFOV* Task = NewAbilityTask<UAbilityTask_SetCameraFOV>(OwningAbility);
    Task->TargetFOV = InTargetFOV;
    Task->InterpSpeed = InInterpSpeed;

    return Task;
}

void UAbilityTask_SetCameraFOV::Activate()
{
    Super::Activate();

    // 카메라 캐싱
    Camera = GetAvatarActor()->GetComponentByClass<UCameraComponent>();
    if(!Camera.IsValid()) EndTask();
}

void UAbilityTask_SetCameraFOV::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    // 현재 FOV 및 목표 FOV 비교
    const float CurrentFOV = Camera->FieldOfView;
    if(FMath::IsNearlyEqual(CurrentFOV, TargetFOV))
    {
        OnEnd.Broadcast();
        EndTask();
    }

    // 보간된 FOV 적용
    const float DesiredFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, InterpSpeed);
    Camera->SetFieldOfView(DesiredFOV);
}
