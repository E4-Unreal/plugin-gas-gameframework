// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFActivatableComponent.h"

void UGGFActivatableComponent::BeginDestroy()
{
    // 타이머 초기화
    if(GetWorld())
    {
        auto& TimerManager = GetWorld()->GetTimerManager();
        if(TimerManager.IsTimerActive(ActivationTimer)) TimerManager.ClearTimer(ActivationTimer);
        if(TimerManager.IsTimerActive(DeactivationTimer)) TimerManager.ClearTimer(DeactivationTimer);
    }

    Super::BeginDestroy();
}

bool UGGFActivatableComponent::TryActivate(AActor* InCauser, AActor* InInstigator)
{
    // 입력 유효성 검사
    if(InCauser == nullptr || InInstigator == nullptr) return false;

    // 중복 호출 방지
    if(ActivationState == EGGFActivationState::Activating || ActivationState == EGGFActivationState::Activated) return false;

    // 비활성화 중인 상태인지 확인
    if(ActivationState == EGGFActivationState::Deactivating)
    {
        // 비활성화 취소
        if(bCanAbort)
        {
            // 비활성화 취소 이벤트 호출
            OnDeactivationAbort.Broadcast(Causer, Instigator);
        }
        else
        {
            // 비활성화가 마무리되기 전까진 활성화할 수 없습니다.
            return false;
        }
    }

    // 활성화 중인 상태로 변경
    ActivationState = EGGFActivationState::Activating;

    // 변수 할당
    Causer = InCauser;
    Instigator = InInstigator;

    // 활성화 시작 이벤트 호출
    OnActivationBegin.Broadcast(Causer, Instigator);

    // 활성화 타이머 설정
    auto& TimerManager = GetWorld()->GetTimerManager();
    if(ActivationDuration > 0)
    {
        ActivationState = EGGFActivationState::Activating;
        TimerManager.SetTimer(ActivationTimer, this, &ThisClass::InternalOnActivationEnd, ActivationDuration);
    }
    else
    {
        InternalOnActivationEnd();
    }

    return true;
}

bool UGGFActivatableComponent::TryDeactivate(AActor* InCauser, AActor* InInstigator)
{
    // 입력 유효성 검사
    if(InCauser == nullptr || InInstigator == nullptr) return false;

    // 중복 호출 방지
    if(ActivationState == EGGFActivationState::Deactivating || ActivationState == EGGFActivationState::Deactivated) return false;

    // 활성화 중인 상태인지 확인
    if(ActivationState == EGGFActivationState::Activating)
    {
        // 활성화 취소
        if(bCanAbort)
        {
            // 활성화 취소 이벤트 호출
            OnActivationAbort.Broadcast(Causer, Instigator);
        }
        else
        {
            // 활성화가 마무리되기 전까진 비활성화할 수 없습니다.
            return false;
        }
    }

    // 비활성화 중인 상태로 변경
    ActivationState = EGGFActivationState::Deactivating;

    // 변수 할당
    Causer = InCauser;
    Instigator = InInstigator;

    // 비활성화 시작 이벤트 호출
    OnDeactivationBegin.Broadcast(Causer, Instigator);

    // 비활성화 타이머 설정
    auto& TimerManager = GetWorld()->GetTimerManager();
    if(DeactivationDuration > 0)
    {
        ActivationState = EGGFActivationState::Deactivating;
        TimerManager.SetTimer(DeactivationTimer, this, &ThisClass::InternalOnDeactivationEnd, DeactivationDuration);
    }
    else
    {
        InternalOnDeactivationEnd();
    }

    return true;
}

void UGGFActivatableComponent::InternalOnActivationEnd()
{
    // 활성화 상태로 변경
    ActivationState = EGGFActivationState::Activated;

    // 활성화 종료 이벤트 호출
    OnActivationEnd.Broadcast(Causer, Instigator);
}

void UGGFActivatableComponent::InternalOnDeactivationEnd()
{
    // 비활성화 상태로 변경
    ActivationState = EGGFActivationState::Deactivated;

    // 비활성화 종료 이벤트 호출
    OnDeactivationEnd.Broadcast(Causer, Instigator);
}
