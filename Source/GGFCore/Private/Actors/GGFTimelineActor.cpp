// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTimelineActor.h"

#include "Components/TimelineComponent.h"

AGGFTimelineActor::AGGFTimelineActor()
{
    Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
    TimelineInterpFunction.BindDynamic(this, &ThisClass::OnTimelineActivated);
    TimelineFinishedFunction.BindDynamic(this, &ThisClass::OnTimelineFinished);

    const ConstructorHelpers::FObjectFinder<UCurveFloat> TimelineCurveFinder(TEXT("/Niagara/DefaultAssets/Curves/Templates/LinearRampUp.LinearRampUp"));
    if(TimelineCurveFinder.Succeeded()) TimelineCurveFloat = TimelineCurveFinder.Object;
}

void AGGFTimelineActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Timeline->AddInterpFloat(TimelineCurveFloat, TimelineInterpFunction);
    Timeline->SetTimelineFinishedFunc(TimelineFinishedFunction);
}

void AGGFTimelineActor::PlayTimeline(bool bReverse, bool bReset)
{
    auto CachedTimeline = GetTimeline();

    if(bUseCustomDuration)
    {
        auto PlayRate = CachedTimeline->GetTimelineLength() / Duration;
        CachedTimeline->SetPlayRate(PlayRate);
    }

    if(bReverse)
    {
        if(bReset) CachedTimeline->ReverseFromEnd();
        else CachedTimeline->Reverse();
    }
    else
    {
        if(bReset) CachedTimeline->PlayFromStart();
        else CachedTimeline->Play();
    }
}

void AGGFTimelineActor::OnTimelineActivated_Implementation(float Value)
{

}

void AGGFTimelineActor::OnTimelineFinished_Implementation()
{
}
