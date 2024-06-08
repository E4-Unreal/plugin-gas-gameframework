// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFTeleportComponent.h"

#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GGFGimmickGameplayTags.h"

UGGFTeleportComponent::UGGFTeleportComponent()
{
    TeleportInCueTag.GameplayCueTag = GameplayCue::Teleport::In::Default;
    TeleportOutCueTag.GameplayCueTag = GameplayCue::Teleport::Out::Default;
}

void UGGFTeleportComponent::Teleport(AActor* ActorToTeleport, AActor* TargetToTeleport)
{
    // InTarget 설정
    if(TargetToTeleport == nullptr)
    {
        TargetToTeleport = Target;
    }

    // 입력 유효성 검사
    if(ActorToTeleport == nullptr || TargetToTeleport == nullptr) return;

    // 순간이동 위치 계산
    FVector DestLocation = TargetToTeleport->GetActorLocation();
    FRotator DestRotation = TargetToTeleport->GetActorRotation();

    DestRotation.Yaw = bUseYaw ? DestRotation.Yaw : 0;
    DestRotation.Pitch = bUsePitch ? DestRotation.Pitch : 0;
    DestRotation.Roll = bUseRoll ? DestRotation.Roll : 0;

    if(auto SourcePawn = Cast<APawn>(ActorToTeleport))
    {
        // 속도 방향 전환
        auto Movement = SourcePawn->GetMovementComponent();
        Movement->Velocity = DestRotation.Vector().GetSafeNormal() * Movement->Velocity.Length();

        // 컨트롤러 회전
        if(SourcePawn->Controller)
        {
            SourcePawn->Controller->SetControlRotation(DestRotation);
        }
    }

    // 순간이동
    ActorToTeleport->TeleportTo(DestLocation, DestRotation);

    // 기존 위치와 목표 위치에 순간이동 이펙트 재생
    HandleGameplayCue(ActorToTeleport, GetOwner(), TeleportInCueTag); // 기존
    HandleGameplayCue(ActorToTeleport, ActorToTeleport, TeleportOutCueTag); // 목표
}

void UGGFTeleportComponent::HandleGameplayCue(AActor* ActorToTeleport, AActor* TargetToHandle, const FGameplayCueTag CueTag)
{
    // 순간이동 이펙트
    FGameplayCueParameters GameplayCueParameters;
    GameplayCueParameters.EffectCauser = GetOwner();
    GameplayCueParameters.Instigator = GetOwner()->GetInstigator();
    GameplayCueParameters.Location = TargetToHandle->GetActorLocation();
    GameplayCueParameters.TargetAttachComponent = TargetToHandle->GetRootComponent();

    UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(TargetToHandle, CueTag.GameplayCueTag, EGameplayCueEvent::Executed, GameplayCueParameters);
}
