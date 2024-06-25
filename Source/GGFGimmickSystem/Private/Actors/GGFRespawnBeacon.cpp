// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFRespawnBeacon.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/GGFGameModeInterface.h"

AGGFRespawnBeacon::AGGFRespawnBeacon()
{
    /* RespawnPlaceholder */
    RespawnPlaceholder = CreateDefaultSubobject<UArrowComponent>(TEXT("RespawnPlaceholder"));
    RespawnPlaceholder->SetupAttachment(RootComponent);
}

void AGGFRespawnBeacon::OnPawnInteract_Implementation(APawn* OtherPawn)
{
    Super::OnPawnInteract_Implementation(OtherPawn);

    if(auto GameMode = GetWorld()->GetAuthGameMode())
    {
        if(GameMode->Implements<UGGFGameModeInterface>())
        {
            const auto& TeamList = IGGFGameModeInterface::Execute_GetTeamListByPlayerController(GameMode, Cast<APlayerController>(OtherPawn->Controller));
            for (auto PlayerController : TeamList)
            {
                if(PlayerController->PlayerState->IsSpectator())
                {
                    FTransform SpawnTransform = GetRespawnPlaceholder()->GetComponentTransform();
                    SpawnTransform.SetScale3D(FVector::OneVector);
                    GameMode->RestartPlayerAtTransform(PlayerController, SpawnTransform);
                    PlayerController->PlayerState->SetIsSpectator(false);
                }
            }
        }
    }
}
