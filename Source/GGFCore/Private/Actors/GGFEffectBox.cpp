// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFEffectBox.h"

#include "Components/BoxComponent.h"
#include "Components/GGFEffectAreaComponent.h"

AGGFEffectBox::AGGFEffectBox(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bReplicates = true;

    /* EffectAreaComponent */
    EffectAreaComponent = CreateDefaultSubobject<UGGFEffectAreaComponent>(TEXT("EffectAreaComponent"));
}

void AGGFEffectBox::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    /* 컴포넌트 초기화 */
    GetEffectAreaComponent()->Init(GetBoxCollision());
}

void AGGFEffectBox::BeginPlay()
{
    Super::BeginPlay();

    if(auto World = GetWorld())
    {
        FHitResult OutHit;
        FCollisionQueryParams CollisionQueryParams;
        CollisionQueryParams.AddIgnoredActor(GetOwner());
        FVector TraceStart = GetActorLocation();
        FVector TraceEnd = GetActorLocation() + -GetActorUpVector() * 1000;
        World->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);

        if(OutHit.bBlockingHit)
        {
            SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, OutHit.ImpactPoint.Z));
        }
    }
}
