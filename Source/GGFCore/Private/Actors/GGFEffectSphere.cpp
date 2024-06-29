// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFEffectSphere.h"

#include "Components/GGFEffectAreaComponent.h"
#include "Components/SphereComponent.h"

AGGFEffectSphere::AGGFEffectSphere(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bReplicates = true;

    /* EffectAreaComponent */
    EffectAreaComponent = CreateDefaultSubobject<UGGFEffectAreaComponent>(TEXT("EffectAreaComponent"));
}

void AGGFEffectSphere::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    /* 컴포넌트 초기화 */
    GetEffectAreaComponent()->Init(GetTriggerSphere());
}
