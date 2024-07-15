// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFFootstepManager.h"

#include "KismetTraceUtils.h"
#include "Logging.h"
#include "Effects/GGFEffectDefinition.h"

UGGFFootstepManager::UGGFFootstepManager()
{
    bWantsInitializeComponent = true;
}

void UGGFFootstepManager::InitializeComponent()
{
    Super::InitializeComponent();

    // 자동 의존성 주입
    if(TargetMesh == nullptr)
    {
        TargetMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
    }
}

void UGGFFootstepManager::SetTargetMesh(USkeletalMeshComponent* NewTargetMesh)
{
    TargetMesh = NewTargetMesh;
}

void UGGFFootstepManager::SpawnLeftFootstepEffect() const
{
    SpawnFootstepEffect(LeftFootstepSocketName);
}

void UGGFFootstepManager::SpawnRightFootstepEffect() const
{
    SpawnFootstepEffect(RightFootstepSocketName);
}

void UGGFFootstepManager::SpawnFootstepEffect(FName FootstepSocketName) const
{
    // 유효성 검사
    if(DefaultFootstepEffect == nullptr)
    {
#if WITH_EDITOR
        LOG_ACTOR_COMPONENT_DETAIL(Warning, TEXT("DefaultFootstepEffect가 설정되지 않았습니다."))
#endif
        return;
    }

    // 소켓 존재 여부 검사
    if(!GetTargetMesh()->DoesSocketExist(FootstepSocketName))
    {
#if WITH_EDITOR
        LOG_ACTOR_COMPONENT_DETAIL(Error, TEXT("%s에 %s 소켓이 존재하지 않습니다."), *GetTargetMesh()->GetName(), *FootstepSocketName.ToString())
#endif
        return;
    }

    // 바닥 표면 재질 검사
    FHitResult TraceHitResult;
    const FVector TraceStart = GetTargetMesh()->GetSocketLocation(FootstepSocketName);
    const FVector TraceEnd = TraceStart + (-GetOwner()->GetActorUpVector() * TraceRange);
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    CollisionQueryParams.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(TraceHitResult, TraceStart, TraceEnd, TraceChannel, CollisionQueryParams);

#if WITH_EDITOR
    if(bShowDebug) DrawDebugLineTraceSingle(GetWorld(), TraceStart, TraceEnd, EDrawDebugTrace::ForDuration, true, TraceHitResult, FLinearColor::Red, FLinearColor::Green, 2);
#endif

    // 스폰할 발 스텝 이펙트 설정
    auto FootstepEffectToSpawn = DefaultFootstepEffect;
    if(TraceHitResult.bBlockingHit)
    {
        if(TraceHitResult.PhysMaterial.IsValid())
        {
            if(FootstepEffectMap.Contains(TraceHitResult.PhysMaterial->SurfaceType))
            {
                FootstepEffectToSpawn = FootstepEffectMap[TraceHitResult.PhysMaterial->SurfaceType];
            }
        }
    }

    // 발 스텝 이펙트 스폰
    FootstepEffectToSpawn->PlayEffectsByHitResult(TraceHitResult);
}
