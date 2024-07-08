// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFJumpPad.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Effects/GGFEffectDefinition.h"

AGGFJumpPad::AGGFJumpPad()
{
    /* 기본 설정 */
    ActorClassToLaunch = AActor::StaticClass();

    /* LaunchDirectionComponent */
    LaunchDirectionComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LaunchDirectionComponent"));
    LaunchDirectionComponent->SetupAttachment(RootComponent);
    LaunchDirectionComponent->SetRelativeRotation(FRotator(90, 0, 0));

    /* 기본 에셋 설정 */
    ConstructorHelpers::FObjectFinder<UGGFEffectDefinition> EffectFinder(TEXT("/GASGameFramework/DataAssets/Effects/JumpPad_Default"));
    if(EffectFinder.Succeeded()) LaunchEffect.EffectDefinition = EffectFinder.Object;
}

void AGGFJumpPad::OnCollisionBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnCollisionBeginOverlap_Implementation(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
                                    SweepResult);

    if(OtherActor->GetClass()->IsChildOf(ActorClassToLaunch))
    {
        Launch(OtherActor);
    }
}

void AGGFJumpPad::Launch_Implementation(AActor* Target)
{
    FVector LaunchVelocity = GetLaunchDirectionComponent()->GetRelativeRotation().Vector() * LaunchPower;

    if(auto Character = Cast<ACharacter>(Target))
    {
        Character->LaunchCharacter(LaunchVelocity, true, true);
    }
    else if(auto PrimitiveComponent = Cast<UPrimitiveComponent>(Target->GetComponentByClass(UPrimitiveComponent::StaticClass())))
    {
        PrimitiveComponent->SetPhysicsLinearVelocity(LaunchVelocity);
    }

    // 점프 이펙트 재생
    if(auto EffectDefinition = LaunchEffect.GetEffectDefinition())
    {
        EffectDefinition->PlayEffectsAtActor(this);
    }
}
