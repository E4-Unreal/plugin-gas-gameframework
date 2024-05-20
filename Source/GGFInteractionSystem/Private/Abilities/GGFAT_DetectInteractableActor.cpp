// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFAT_DetectInteractableActor.h"

#include "KismetTraceUtils.h"
#include "Interfaces/GGFInteractableInterface.h"

UGGFAT_DetectInteractableActor::UGGFAT_DetectInteractableActor()
{
    bTickingTask = true;
}

UGGFAT_DetectInteractableActor* UGGFAT_DetectInteractableActor::CreateTask(UGameplayAbility* OwningAbility,
    bool ShowDebug, float InMaxDistance, float InSphereRadius)
{
    auto NewTask = NewAbilityTask<UGGFAT_DetectInteractableActor>(OwningAbility);
    NewTask->MaxDistance = InMaxDistance;
    NewTask->SphereRadius = InSphereRadius;
#if WITH_EDITOR
    NewTask->bShowDebug = ShowDebug;
#endif

    return NewTask;
}

void UGGFAT_DetectInteractableActor::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    Scan(DeltaTime);
}

void UGGFAT_DetectInteractableActor::Scan(float DeltaTime)
{
    AActor* AvatarActor = GetAvatarActor();

    // 유효성 검사
    UWorld* World = AvatarActor->GetWorld();
    if(World == nullptr) return;

    // 멀티 라인 트레이스를 위한 변수 설정
    FMinimalViewInfo ViewInfo;
    AvatarActor->CalcCamera(DeltaTime, ViewInfo);
    float Offset = (AvatarActor->GetActorLocation() - ViewInfo.Location).Size();
    const FVector TraceStart = ViewInfo.Location + Offset * ViewInfo.Rotation.Vector();
    const FVector TraceEnd = TraceStart + MaxDistance * ViewInfo.Rotation.Vector();
    ECollisionChannel CollisionChannel = ECC_Visibility;
    TArray<FHitResult> OutHits;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(AvatarActor);

    // 멀티 라인 트레이스
    const bool bHit = World->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, FQuat::Identity, CollisionChannel, FCollisionShape::MakeSphere(SphereRadius), Params);

#if WITH_EDITOR
    // 디버그 시각화
    if(bShowDebug)
    {
        DrawDebugSphereTraceMulti(World, TraceStart, TraceEnd, SphereRadius, EDrawDebugTrace::ForOneFrame, bHit, OutHits, FLinearColor::Red, FLinearColor::Green, 1);
    }
#endif

    // 상호작용 가능한 오브젝트 탐색
    AActor* InteractableActor = nullptr;
    if(bHit)
    {
        for (const FHitResult& OutHit : OutHits)
        {
            // Owner와 관련된 액터인 경우 추가 검사 진행
            // 무기나 장비 등으로 인해 시야를 가리는 형상 방지
            if(OutHit.GetActor()->GetOwner() == AvatarActor) continue;

            // 새로운 상호작용 가능한 오브젝트 설정
            if(OutHit.GetActor()->Implements<UGGFInteractableInterface>())
            {
                InteractableActor = OutHit.GetActor();
            }

            break;
        }
    }

    // 이벤트 호출
    OnInteractableActorDetected.Broadcast(InteractableActor);
}
