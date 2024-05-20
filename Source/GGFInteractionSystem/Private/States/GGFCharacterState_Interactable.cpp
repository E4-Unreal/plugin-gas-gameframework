// Fill out your copyright notice in the Description page of Project Settings.

#include "States/GGFCharacterState_Interactable.h"

#include "GGFInteractionGameplayTags.h"
#include "KismetTraceUtils.h"
#include "Interfaces/GGFInteractableInterface.h"

UGGFCharacterState_Interactable::UGGFCharacterState_Interactable()
{
    StateTag = GGFGameplayTags::State::Interactable;
}

void UGGFCharacterState_Interactable::Scan(float DeltaTime)
{
    // 유효성 검사
    UWorld* World = GetOwner()->GetWorld();
    if(World == nullptr) return;

    // 멀티 라인 트레이스를 위한 변수 설정
    FMinimalViewInfo ViewInfo;
    GetOwner()->CalcCamera(DeltaTime, ViewInfo);
    float Offset = (GetOwner()->GetActorLocation() - ViewInfo.Location).Size();
    const FVector TraceStart = ViewInfo.Location + Offset * ViewInfo.Rotation.Vector();
    const FVector TraceEnd = TraceStart + MaxDistance * ViewInfo.Rotation.Vector();
    ECollisionChannel CollisionChannel = ECC_Visibility;
    TArray<FHitResult> OutHits;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());

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
    if(bHit)
    {
        for (const FHitResult& OutHit : OutHits)
        {
            // Owner와 관련된 액터인 경우 추가 검사 진행
            // 무기나 장비 등으로 인해 시야를 가리는 형상 방지
            if(OutHit.GetActor()->GetOwner() == GetOwner()) continue;

            // 이미 등록된 오브젝트인 경우 아무런 동작도 하지 않음
            if(OutHit.GetActor() == InteractableActor) return;

            // 기존 오브젝트 비활성화
            Deactivate();

            // 새로운 상호작용 가능한 오브젝트 설정
            if(OutHit.GetActor()->Implements<UGGFInteractableInterface>())
            {
                InteractableActor = OutHit.GetActor();
                Activate();
            }

            return;
        }
    }
}

void UGGFCharacterState_Interactable::Activate()
{
    if(InteractableActor)
    {
        IGGFInteractableInterface::Execute_Activate(InteractableActor, GetOwner());
    }
}

void UGGFCharacterState_Interactable::Deactivate()
{
    if(InteractableActor)
    {
        IGGFInteractableInterface::Execute_Deactivate(InteractableActor, GetOwner());
        InteractableActor = nullptr;
    }
}

void UGGFCharacterState_Interactable::OnTick_Implementation(float DeltaTime)
{
    Scan(DeltaTime);
}

void UGGFCharacterState_Interactable::OnExit_Implementation()
{
    Deactivate();
}
