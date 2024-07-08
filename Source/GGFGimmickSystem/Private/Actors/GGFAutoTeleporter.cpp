// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFAutoTeleporter.h"
#include "Components/GGFTeleportComponent.h"

AGGFAutoTeleporter::AGGFAutoTeleporter()
{
    /* TeleportComponent */
    TeleportComponent = CreateDefaultSubobject<UGGFTeleportComponent>(TEXT("TeleportComponent"));
}

void AGGFAutoTeleporter::OnCollisionBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    Super::OnCollisionBeginOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex,
                                                  bFromSweep, SweepResult);

    GetTeleportComponent()->Teleport(OtherActor);
}
