// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFJumpPad.h"

#include "GEBlueprintFunctionLibrary.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "GGFGimmickGameplayTags.h"

AGGFJumpPad::AGGFJumpPad()
{
    /* LaunchDirectionComponent */
    LaunchDirectionComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LaunchDirectionComponent"));
    LaunchDirectionComponent->SetupAttachment(RootComponent);
    LaunchDirectionComponent->SetRelativeRotation(FRotator(90, 0, 0));

    /* 기본 설정 */
    ActorClassToLaunch = AActor::StaticClass();
    LaunchCueTag.GameplayCueTag = GameplayCue::Launch::Default;
}

void AGGFJumpPad::OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnTriggerBoxBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
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

    UGEBlueprintFunctionLibrary::LocalHandleGameplayCue(this, LaunchCueTag);
}
