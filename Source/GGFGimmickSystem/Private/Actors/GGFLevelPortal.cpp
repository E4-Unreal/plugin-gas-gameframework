// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFLevelPortal.h"
#include "GGFGameMode.h"

AGGFLevelPortal::AGGFLevelPortal()
{
    /* 기본 설정 */
    bServerOnly = true;
}

void AGGFLevelPortal::OnCollisionBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                             AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                             const FHitResult& SweepResult)
{
    Super::OnCollisionBeginOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex,
                                                  bFromSweep, SweepResult);

    // 유효성 검사
    if(DestinationLevel.IsNull()) return;

    // 서버 레벨 이동
    if(auto Pawn = Cast<APawn>(OtherActor))
    {
        if(Pawn->IsPlayerControlled())
        {
            if(auto GameMode = Cast<AGGFGameMode>(GetWorld()->GetAuthGameMode()))
            {
                GameMode->ServerTravelBySoftObjectPtr(DestinationLevel);
            }
        }
    }
}
