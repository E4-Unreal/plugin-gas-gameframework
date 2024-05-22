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

    // 플레이어 폰 검사
    APawn* PlayerPawn = ConvertActorToPlayerPawn(OtherActor);
    if(PlayerPawn == nullptr) return false;

    // 플레이어 폰인 경우
    OnPlayerPawnActivate(PlayerPawn);

    // 로컬 플레이어 폰인 경우
    if(PlayerPawn->IsLocallyControlled()) OnLocalPlayerPawnActivate(PlayerPawn);

    return true;
}

bool AGGFInteractableActorBase::Deactivate_Implementation(AActor* OtherActor)
{
    // TODO 외곽선 및 UI 숨기기 등
#if WITH_EDITOR
    if(OtherActor)
    {
        FString NetRole = HasAuthority() ? "Server" : "Client";
        UE_LOG(LogGGFInteraction, Log, TEXT("%s Deactivate: %s > %s"), *NetRole, *OtherActor->GetName(), *GetName())
    }
#endif

    // 플레이어 폰 검사
    APawn* PlayerPawn = ConvertActorToPlayerPawn(OtherActor);
    if(PlayerPawn == nullptr) return false;

    // 플레이어 폰인 경우
    OnPlayerPawnDeactivate(PlayerPawn);

    // 로컬 플레이어 폰인 경우
    if(PlayerPawn->IsLocallyControlled()) OnLocalPlayerPawnDeactivate(PlayerPawn);

    return true;
}

bool AGGFInteractableActorBase::StartInteraction_Implementation(AActor* OtherActor)
{
    // TODO 상호작용 동작 시작
#if WITH_EDITOR
    if(OtherActor)
    {
        FString NetRole = HasAuthority() ? "Server" : "Client";
        UE_LOG(LogGGFInteraction, Log, TEXT("%s Start Interaction: %s > %s"), *NetRole, *OtherActor->GetName(), *GetName())
    }
#endif

    // 플레이어 폰 검사
    APawn* PlayerPawn = ConvertActorToPlayerPawn(OtherActor);
    if(PlayerPawn == nullptr) return false;

    // 플레이어 폰인 경우
    OnPlayerPawnStartInteraction(PlayerPawn);

    // 로컬 플레이어 폰인 경우
    if(PlayerPawn->IsLocallyControlled()) OnLocalPlayerPawnStartInteraction(PlayerPawn);

    return true;
}

bool AGGFInteractableActorBase::StopInteraction_Implementation(AActor* OtherActor)
{
    // TODO 상호작용 동작 종료
#if WITH_EDITOR
    if(OtherActor)
    {
        FString NetRole = HasAuthority() ? "Server" : "Client";
        UE_LOG(LogGGFInteraction, Log, TEXT("%s Stop Interaction: %s > %s"), *NetRole, *OtherActor->GetName(), *GetName())
    }
#endif

    // 플레이어 폰 검사
    APawn* PlayerPawn = ConvertActorToPlayerPawn(OtherActor);
    if(PlayerPawn == nullptr) return false;

    // 플레이어 폰인 경우
    OnPlayerPawnStopInteraction(PlayerPawn);

    // 로컬 플레이어 폰인 경우
    if(PlayerPawn->IsLocallyControlled()) OnLocalPlayerPawnStopInteraction(PlayerPawn);

    return true;
}

APawn* AGGFInteractableActorBase::ConvertActorToPlayerPawn(AActor* OtherActor)
{
    // 플레이어 폰 검사
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if(OtherPawn && OtherPawn->IsPlayerControlled()) return OtherPawn;

    return nullptr;
}

void AGGFInteractableActorBase::OnPlayerPawnActivate_Implementation(APawn* PlayerPawn)
{
}

void AGGFInteractableActorBase::OnPlayerPawnDeactivate_Implementation(APawn* PlayerPawn)
{
}

void AGGFInteractableActorBase::OnPlayerPawnStartInteraction_Implementation(APawn* PlayerPawn)
{
}

void AGGFInteractableActorBase::OnPlayerPawnStopInteraction_Implementation(APawn* PlayerPawn)
{
}

void AGGFInteractableActorBase::OnLocalPlayerPawnActivate_Implementation(APawn* LocalPlayerPawn)
{
}

void AGGFInteractableActorBase::OnLocalPlayerPawnDeactivate_Implementation(APawn* LocalPlayerPawn)
{
}

void AGGFInteractableActorBase::OnLocalPlayerPawnStartInteraction_Implementation(APawn* LocalPlayerPawn)
{
}

void AGGFInteractableActorBase::OnLocalPlayerPawnStopInteraction_Implementation(APawn* LocalPlayerPawn)
{
}
