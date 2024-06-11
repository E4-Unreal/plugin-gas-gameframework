// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFActivatableComponent.h"

#include "Sound/SoundCue.h"

UGGFActivatableComponent::UGGFActivatableComponent()
{
    /* 기본 에셋 설정 */
    static ConstructorHelpers::FObjectFinder<USoundCue> SoundFinder(TEXT("/LyraContent/Custom/SoundCues/Effects/SC_Button_01"));
    if (SoundFinder.Succeeded())
    {
        ActivationSound = SoundFinder.Object;
        DeactivationSound = SoundFinder.Object;
    }
}

bool UGGFActivatableComponent::TryActivate(AActor* NewActivator, bool bForce)
{
    // 유효성 검사
    if(NewActivator == nullptr) return false;

    // 중복 호출 검사
    if(!bForce && bActivated) return false;

    // 변수 할당
    Activator = NewActivator;

    // 타이머 초기화
    ResetTimer();

    // 활성화 사운드 재생
    PlaySound(ActivationSound, ActivationDuration);

    // 이벤트 호출
    OnBeginActivate.Broadcast(Activator);

    if(FMath::IsNearlyZero(ActivationDuration))
    {
        // 즉시 활성화 종료
        InternalOnEndActivate();
    }
    else
    {
        // 활성화 종료 타이머 설정
        GetOwner()->GetWorldTimerManager().SetTimer(ActivationTimerHandle, this, &ThisClass::InternalOnEndActivate, ActivationDuration);
    }

    return true;
}

bool UGGFActivatableComponent::TryDeactivate(AActor* NewActivator, bool bForce)
{
    // 유효성 검사
    if(NewActivator == nullptr) return false;

    // 중복 호출 검사
    if(!bForce && !bActivated) return false;

    // 변수 할당
    Activator = NewActivator;

    // 타이머 초기화
    ResetTimer();

    // 비활성화 사운드 재생
    PlaySound(DeactivationSound, DeactivationDuration);

    // 이벤트 호출
    OnBeginDeactivate.Broadcast(Activator);

    if(FMath::IsNearlyZero(DeactivationDuration))
    {
        // 즉시 활성화 종료
        InternalOnEndDeactivate();
    }
    else
    {
        // 타이머 설정
        GetOwner()->GetWorldTimerManager().SetTimer(DeactivationTimerHandle, this, &ThisClass::InternalOnEndDeactivate, DeactivationDuration);
    }

    return false;
}

void UGGFActivatableComponent::PlaySound(USoundCue* NewSound, float Duration)
{
    // 기존 소리 재생 중지
    Stop();

    // 유효성 검사
    if(NewSound == nullptr) return;

    // 소리 설정
    SetSound(NewSound);

    // 재생
    float PlayRate = FMath::IsNearlyZero(Duration) ? 1 : NewSound->MaxDistance / Duration;
    SetPitchMultiplier(PlayRate);
    Play();
}

void UGGFActivatableComponent::ResetTimer()
{
    // 타이머 초기화
    auto& TimerManager = GetOwner()->GetWorldTimerManager();
    if(TimerManager.IsTimerActive(DeactivationTimerHandle))
    {
        TimerManager.ClearTimer(DeactivationTimerHandle);
        OnAbortDeactivate.Broadcast(Activator);
    }
    else if(TimerManager.IsTimerActive(ActivationTimerHandle))
    {
        TimerManager.ClearTimer(ActivationTimerHandle);
        OnAbortActivate.Broadcast(Activator);
    }
}

void UGGFActivatableComponent::InternalOnEndActivate()
{
    OnEndActivate.Broadcast(Activator);
}

void UGGFActivatableComponent::InternalOnEndDeactivate()
{
    OnEndDeactivate.Broadcast(Activator);
}
