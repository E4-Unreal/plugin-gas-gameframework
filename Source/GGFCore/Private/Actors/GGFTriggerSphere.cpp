// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerSphere.h"

#include "Components/SphereComponent.h"

AGGFTriggerSphere::AGGFTriggerSphere(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* TriggerSphere */
    TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
    SetRootComponent(TriggerSphere);
}

void AGGFTriggerSphere::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    GetTriggerSphere()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerSphereBeginOverlap);
    GetTriggerSphere()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnTriggerSphereEndOverlap);
}

void AGGFTriggerSphere::OnTriggerSphereBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                                   AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                                   const FHitResult& SweepResult)
{
}

void AGGFTriggerSphere::OnTriggerSphereEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
