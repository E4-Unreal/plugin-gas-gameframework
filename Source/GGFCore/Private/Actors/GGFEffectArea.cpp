// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFEffectArea.h"

#include "Components/BoxComponent.h"
#include "Components/GGFEffectAreaComponent.h"

AGGFEffectArea::AGGFEffectArea(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* EffectAreaComponent */
    EffectAreaComponent = CreateDefaultSubobject<UGGFEffectAreaComponent>(TEXT("EffectAreaComponent"));
}

void AGGFEffectArea::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    /* 컴포넌트 초기화 */
    GetEffectAreaComponent()->Init(GetTriggerBox());
}
