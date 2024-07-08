// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerSphere.h"

AGGFTriggerSphere::AGGFTriggerSphere(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USphereComponent>(CollisionName))
{

}
