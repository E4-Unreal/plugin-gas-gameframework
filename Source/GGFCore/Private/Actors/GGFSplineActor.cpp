// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFSplineActor.h"

#include "Components/SplineComponent.h"

AGGFSplineActor::AGGFSplineActor()
{
    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SetRootComponent(SplineComponent);
}
