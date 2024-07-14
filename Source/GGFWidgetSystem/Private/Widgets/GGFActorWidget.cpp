// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFActorWidget.h"

void UGGFActorWidget::SetActor(AActor* NewActor)
{
    // PlayerActor 교체
    auto OldPlayerActor = Actor;
    Actor = NewActor;

    if(OldPlayerActor.IsValid())
    {
        // 기존 Actor 이벤트 언바인딩
        UnbindActorEvents(OldPlayerActor.Get());
    }

    if(Actor.IsValid())
    {
        // 새로운 Actor 이벤트 바인딩
        BindActorEvents(Actor.Get());

        // Actor 현재 정보 반영
        Fetch();
    }
}

void UGGFActorWidget::Fetch()
{
}

void UGGFActorWidget::BindActorEvents(AActor* NewActor)
{
}

void UGGFActorWidget::UnbindActorEvents(AActor* OldActor)
{
}
