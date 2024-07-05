﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFAutoTeleporter.h"
#include "Components/GGFTeleportComponent.h"

AGGFAutoTeleporter::AGGFAutoTeleporter()
{
    /* TeleportComponent */
    TeleportComponent = CreateDefaultSubobject<UGGFTeleportComponent>(TEXT("TeleportComponent"));
}

void AGGFAutoTeleporter::OnCollisionComponentBeginOverlapPawn_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                                     APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                                     const FHitResult& SweepResult)
{
    GetTeleportComponent()->Teleport(OtherPawn);

    Super::OnCollisionComponentBeginOverlapPawn_Implementation(OverlappedComponent, OtherPawn, OtherComp, OtherBodyIndex,
                                                       bFromSweep, SweepResult);
}
