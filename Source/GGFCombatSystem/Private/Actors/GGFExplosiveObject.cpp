// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFExplosiveObject.h"

#include "Components/GGFExplosiveComponent.h"
#include "Components/SphereComponent.h"

AGGFExplosiveObject::AGGFExplosiveObject()
{
    // 리플리케이트 설정
    SetReplicates(true);

    // ExplosionArea
    ExplosionArea = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionSphere"));
    ExplosionArea->SetupAttachment(RootComponent);
    ExplosionArea->SetSphereRadius(200);

    // ExplosiveComponent
    ExplosiveComponent = CreateDefaultSubobject<UGGFExplosiveComponent>(TEXT("ExplosiveComponent"));
    ExplosiveComponent->Init(ExplosionArea);
}

void AGGFExplosiveObject::Destroyed()
{
    ExplosiveComponent->Explode();

    Super::Destroyed();
}

void AGGFExplosiveObject::OnDead_Implementation()
{
    Destroy();
}
