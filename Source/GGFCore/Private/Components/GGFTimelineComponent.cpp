// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFTimelineComponent.h"

UGGFTimelineComponent::UGGFTimelineComponent()
{
    /* 기본 설정 */
    PrimaryComponentTick.bCanEverTick = true;

    /* 기본 에셋 설정 */
    const ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFloatFinder(TEXT("/Niagara/DefaultAssets/Curves/Templates/LinearRampUp.LinearRampUp"));
    if(CurveFloatFinder.Succeeded()) CurveFloat = CurveFloatFinder.Object;
}

void UGGFTimelineComponent::InitializeComponent()
{
    Super::InitializeComponent();

    bValid = bValid && CurveFloat;
}

void UGGFTimelineComponent::BeginPlay()
{
    Super::BeginPlay();

    // 이벤트 바인딩
    InterpFunction.BindDynamic(this, &ThisClass::InternalOnActivated);
    Timeline.AddInterpFloat(CurveFloat, InterpFunction);

    FinishedFunction.BindDynamic(this, &ThisClass::InternalOnFinished);
    Timeline.SetTimelineFinishedFunc(FinishedFunction);
}

void UGGFTimelineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    Timeline.TickTimeline(DeltaTime);
}

void UGGFTimelineComponent::PlayTimeline(bool bReverse, bool bReset)
{
    // 유효성 검사
    if(CurveFloat == nullptr) return;

    // 타임라인 재생 시간 설정
    Timeline.SetTimelineLength(Duration);

    if(bReverse)
    {
        if(bReset) Timeline.ReverseFromEnd();
        else Timeline.Reverse();
    }
    else
    {
        if(bReset) Timeline.PlayFromStart();
        else Timeline.Play();
    }
}

void UGGFTimelineComponent::InternalOnActivated(float Value)
{
    OnActivated.Broadcast(Value);
}

void UGGFTimelineComponent::InternalOnFinished()
{
    OnFinished.Broadcast();
}
