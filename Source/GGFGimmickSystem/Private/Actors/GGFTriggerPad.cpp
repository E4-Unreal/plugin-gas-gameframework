// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerPad.h"

#include "Components/BoxComponent.h"
#include "Components/GGFEffectManager.h"
#include "Components/GGFTriggerComponent.h"
#include "Effects/GGFEffectDefinition.h"
#include "GameFramework/Character.h"

AGGFTriggerPad::AGGFTriggerPad()
{
    /* 기본 설정 */
    TriggerConditionMap.Emplace(ACharacter::StaticClass(), 1);

    /* TriggerComponent */
    TriggerComponent = CreateDefaultSubobject<UGGFTriggerComponent>(TEXT("TriggerComponent"));

    /* 기본 에셋 설정 */
    {
        ConstructorHelpers::FObjectFinder<UGGFEffectDefinition> EffectFinder(TEXT("/GASGameFramework/DataAssets/Effects/Activate_Default"));
        if(EffectFinder.Succeeded()) ActivateEffect.EffectDefinition = EffectFinder.Object;
    }

    {
        ConstructorHelpers::FObjectFinder<UGGFEffectDefinition> EffectFinder(TEXT("/GASGameFramework/DataAssets/Effects/Deactivate_Default"));
        if(EffectFinder.Succeeded()) DeactivateEffect.EffectDefinition = EffectFinder.Object;
    }
}

void AGGFTriggerPad::OnCollisionBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnCollisionBeginOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
                                    SweepResult);

    // 트리거 조건 만족 여부에 따라 활성화 혹은 비활성화
    CheckTriggerCondition();
}

void AGGFTriggerPad::OnCollisionEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    Super::OnCollisionEndOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

    // 트리거 조건 만족 여부에 따라 활성화 혹은 비활성화
    CheckTriggerCondition();
}

void AGGFTriggerPad::CheckTriggerCondition()
{
    // 조건 달성
    if(IsTriggerConditionSatisfied())
    {
        GetTriggerComponent()->ActivateTargets(this);

        // 한 번만 트리거가 동작하도록 설정된 경우 오버랩 이벤트 언바인딩
        if(!GetTriggerComponent()->bCanRetrigger)
        {
            UnbindOverlapEvents();
        }
    }
    else // 조건 달성 실패
    {
        GetTriggerComponent()->DeactivateTargets(this);
    }
}

bool AGGFTriggerPad::IsTriggerConditionSatisfied()
{
    for (const auto& [ActorClass, Num] : TriggerConditionMap)
    {
        TArray<AActor*> OverlappingActors;
        GetBoxCollision()->GetOverlappingActors(OverlappingActors, ActorClass);
        OverlappingActors.RemoveSwap(this);

        if(OverlappingActors.Num() < Num) return false;
    }

    return true;
}

bool AGGFTriggerPad::TryActivate_Implementation(AActor* InCauser, AActor* InInstigator)
{
    if(auto EffectDefinition = ActivateEffect.GetEffectDefinition())
    {
        EffectDefinition->PlayEffectsAtActor(this);
    }

    return true;
}

bool AGGFTriggerPad::TryDeactivate_Implementation(AActor* InCauser, AActor* InInstigator)
{
    if(auto EffectDefinition = DeactivateEffect.GetEffectDefinition())
    {
        EffectDefinition->PlayEffectsAtActor(this);
    }

    return true;
}
