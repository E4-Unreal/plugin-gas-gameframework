// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFExplosiveObject.h"

#include "Components/GGFExplosiveComponent.h"
#include "Components/SphereComponent.h"

AGGFExplosiveObject::AGGFExplosiveObject()
{
    // ExplosionArea
    ExplosionArea = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
    ExplosionArea->SetupAttachment(RootComponent);
    ExplosionArea->SetSphereRadius(400);

    // ExplosiveComponent
    ExplosiveComponent = CreateDefaultSubobject<UGGFExplosiveComponent>(TEXT("ExplosiveComponent"));
    ExplosiveComponent->Init(ExplosionArea);
}

void AGGFExplosiveObject::Destroyed()
{
    ExplosiveComponent->Explode();

    Super::Destroyed();
}
