// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTimelineActor.h"

#include "Components/GGFTimelineComponent.h"

AGGFTimelineActor::AGGFTimelineActor()
{
    Timeline = CreateDefaultSubobject<UGGFTimelineComponent>(TEXT("Timeline"));
}

void AGGFTimelineActor::BeginPlay()
{
    Super::BeginPlay();

    // 이벤트 바인딩
    GetTimeline()->OnActivated.AddDynamic(this, &ThisClass::OnTimelineActivated);
    GetTimeline()->OnFinished.AddDynamic(this, &ThisClass::OnTimelineFinished);
}

void AGGFTimelineActor::OnTimelineActivated_Implementation(float Value)
{

}

void AGGFTimelineActor::OnTimelineFinished_Implementation()
{
}
