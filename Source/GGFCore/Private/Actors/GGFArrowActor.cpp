// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFArrowActor.h"

#include "Components/ArrowComponent.h"

AGGFArrowActor::AGGFArrowActor()
{
    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
    SetRootComponent(ArrowComponent);
}
