﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerPad.h"

#include "GEBlueprintFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/GGFTriggerComponent.h"
#include "GameFramework/Character.h"
#include "GGFGimmickGameplayTags.h"

AGGFTriggerPad::AGGFTriggerPad()
{
    /* TriggerComponent */
    TriggerComponent = CreateDefaultSubobject<UGGFTriggerComponent>(TEXT("TriggerComponent"));

    /* 기본 설정 */
    TriggerConditionMap.Emplace(ACharacter::StaticClass(), 1);
    ActivateCueTag.GameplayCueTag = GameplayCue::Button::Activate;
    DeactivateCueTag.GameplayCueTag = GameplayCue::Button::Deactivate;
}

void AGGFTriggerPad::OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnTriggerBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
                                    SweepResult);

    // 트리거 조건 만족 여부에 따라 활성화 혹은 비활성화
    CheckTriggerCondition();
}

void AGGFTriggerPad::OnTriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnTriggerBoxEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

    // 트리거 조건 만족 여부에 따라 활성화 혹은 비활성화
    CheckTriggerCondition();
}

void AGGFTriggerPad::CheckTriggerCondition()
{
    // 중복 호출 방지
    if(bTriggerOnce && GetTriggerComponent()->IsActivated()) return;

    if(IsTriggerConditionSatisfied())
    {
        if(bTriggerOnce)
        {
            UnBindTriggerBoxEvents();
        }

        GetTriggerComponent()->ActivateTargets();
    }
    else
    {
        GetTriggerComponent()->DeactivateTargets();
    }
}

bool AGGFTriggerPad::IsTriggerConditionSatisfied()
{
    for (const auto& [ActorClass, Num] : TriggerConditionMap)
    {
        TArray<AActor*> OverlappingActors;
        GetTriggerBox()->GetOverlappingActors(OverlappingActors, ActorClass);
        OverlappingActors.RemoveSwap(this);

        if(OverlappingActors.Num() < Num) return false;
    }

    return true;
}

bool AGGFTriggerPad::Activate_Implementation(AActor* InstigatorActor)
{
    UGEBlueprintFunctionLibrary::LocalHandleGameplayCue(this, ActivateCueTag);
    return true;
}

bool AGGFTriggerPad::Deactivate_Implementation(AActor* InstigatorActor)
{
    UGEBlueprintFunctionLibrary::LocalHandleGameplayCue(this, DeactivateCueTag);
    return true;
}
