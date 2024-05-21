// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableActorBase.h"

#include "Logging.h"

AGGFInteractableActorBase::AGGFInteractableActorBase(const FObjectInitializer& ObjectInitializer)
{
    /* 기본 설정 */
    // 리플리케이트 설정
    bReplicates = true;

    /* DefaultSceneComponent */
    // 서브 오브젝트 생성
    DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));

    // 계층 설정
    SetRootComponent(DefaultScene);
}

bool AGGFInteractableActorBase::Activate_Implementation(AActor* OtherActor)
{
    // TODO 외곽선 및 UI 표시 등
#if WITH_EDITOR
    if(OtherActor)
    {
        FString NetRole = HasAuthority() ? "Server" : "Client";
        UE_LOG(LogGGFInteraction, Log, TEXT("%s Activate: %s > %s"), *NetRole, *OtherActor->GetName(), *GetName())
    }
#endif
    return OtherActor != nullptr;
}

bool AGGFInteractableActorBase::Deactivate_Implementation(AActor* OtherActor)
{
    // TODO 외곽선 및 UI 숨기기 등
#if WITH_EDITOR
    if(OtherActor)
    {
        FString NetRole = HasAuthority() ? "Server" : "Client";
        UE_LOG(LogGGFInteraction, Log, TEXT("%s Deactivate: %s > %s"), *NetRole, *OtherActor->GetName(), *GetName())
        return true;
    }
#endif
    return OtherActor != nullptr;
}

bool AGGFInteractableActorBase::StartInteraction_Implementation(AActor* OtherActor)
{
    // TODO 상호작용 동작 시작
#if WITH_EDITOR
    if(OtherActor)
    {
        FString NetRole = HasAuthority() ? "Server" : "Client";
        UE_LOG(LogGGFInteraction, Log, TEXT("%s Start Interaction: %s > %s"), *NetRole, *OtherActor->GetName(), *GetName())
        return true;
    }
#endif
    return OtherActor != nullptr;
}

bool AGGFInteractableActorBase::StopInteraction_Implementation(AActor* OtherActor)
{
    // TODO 상호작용 동작 종료
#if WITH_EDITOR
    if(OtherActor)
    {
        FString NetRole = HasAuthority() ? "Server" : "Client";
        UE_LOG(LogGGFInteraction, Log, TEXT("%s Stop Interaction: %s > %s"), *NetRole, *OtherActor->GetName(), *GetName())
        return true;
    }
#endif
    return OtherActor != nullptr;
}
