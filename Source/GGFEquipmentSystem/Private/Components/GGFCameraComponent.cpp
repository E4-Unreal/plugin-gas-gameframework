// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFCameraComponent.h"

UGGFCameraComponent::UGGFCameraComponent()
{
    bWantsInitializeComponent = true;
    PrimaryComponentTick.bCanEverTick = true;
}

void UGGFCameraComponent::InitializeComponent()
{
    Super::InitializeComponent();

    // 기본값 캐싱
    DefaultFOV = FieldOfView;
    TargetFOV = DefaultFOV;
}

void UGGFCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(bInterpolatingFOV)
    {
        FieldOfView = FMath::FInterpTo(FieldOfView, TargetFOV, DeltaTime, InterpSpeed);
        if(FMath::IsNearlyEqual(FieldOfView, TargetFOV))
        {
            bInterpolatingFOV = false;
            OnSetFOVFinished.Broadcast();
        }
    }
}

void UGGFCameraComponent::SetFieldOfView(float InFieldOfView)
{
    TargetFOV = InFieldOfView <= 0 ? DefaultFOV : InFieldOfView;
    bInterpolatingFOV = true;
}
