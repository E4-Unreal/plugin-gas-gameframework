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

#if WITH_EDITOR
    if(bUseTick)
    {
        FVector Target = GetTargetLocation();
    }
#endif
}

void UGGFCameraComponent::SetFieldOfView(float InFieldOfView)
{
    TargetFOV = InFieldOfView <= 0 ? DefaultFOV : InFieldOfView;
    bInterpolatingFOV = true;
}

FVector UGGFCameraComponent::GetTargetLocation() const
{
    if(UWorld* World = GetWorld())
    {
        // 카메라를 기준으로 라인 트레이스를 위한 위치 계산
        const FVector ForwardVector = GetForwardVector();
        FVector OffsetVector = GetOwner()->GetActorLocation() - GetComponentLocation();
        OffsetVector.Z = 0;
        float Offset = OffsetVector.Dot(ForwardVector) + TraceOffset;
        const FVector& TraceStart = GetComponentLocation() + Offset * ForwardVector;
        const FVector& TraceEnd = TraceStart + 100000.f * ForwardVector;
        FHitResult HitResult;

        // 자기 자신 제외
        FCollisionQueryParams CollisionQueryParams;
        CollisionQueryParams.AddIgnoredActor(GetOwner());

        // 라인 트레이스
        World->LineTraceSingleByChannel(
            HitResult,
            TraceStart,
            TraceEnd,
            TraceChannel,
            CollisionQueryParams
            );

        FVector Target = HitResult.bBlockingHit ? HitResult.Location : TraceEnd;

#if WITH_EDITOR
        if(bShowDebug)
        {
            if(bUseTick)
            {
                DrawDebugLine(World, TraceStart, Target, FColor::Red);
                DrawDebugSphere(World, Target, 10, 12, FColor::Red);
                DrawDebugLine(World, Target, TraceEnd, FColor::Green);
            }
            else
            {
                DrawDebugLine(World, TraceStart, Target, FColor::Red, false, LifeTime);
                DrawDebugSphere(World, Target, 10, 12, FColor::Red, false, LifeTime);
                DrawDebugLine(World, Target, TraceEnd, FColor::Green, false, LifeTime);
            }
        }
#endif

        return Target;
    }

    return FVector::ZeroVector;
}
