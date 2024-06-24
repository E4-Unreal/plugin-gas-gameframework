// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFEffectTriggerBox.h"

#include "Components/BoxComponent.h"
#include "Components/GGFEffectAreaComponent.h"

AGGFEffectTriggerBox::AGGFEffectTriggerBox(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* EffectAreaComponent */
    EffectAreaComponent = CreateDefaultSubobject<UGGFEffectAreaComponent>(TEXT("EffectAreaComponent"));
}

void AGGFEffectTriggerBox::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    /* 컴포넌트 초기화 */
    GetEffectAreaComponent()->Init(GetTriggerBox());
}
