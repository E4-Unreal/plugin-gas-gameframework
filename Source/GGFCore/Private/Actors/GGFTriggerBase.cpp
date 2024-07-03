// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerBase.h"

#include "Logging.h"
#include "Components/ShapeComponent.h"

FName AGGFTriggerBase::DefaultSceneName(TEXT("DefaultScene"));
FName AGGFTriggerBase::CollisionComponentName(TEXT("CollisionComponent"));
FName AGGFTriggerBase::DisplayMeshName(TEXT("DisplayMesh"));

AGGFTriggerBase::AGGFTriggerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    /* DefaultScene */
    DefaultScene = CreateDefaultSubobject<USceneComponent>(DefaultSceneName);
    SetRootComponent(DefaultScene);

    /* CollisionComponent */
    CollisionComponent = CreateDefaultSubobject<UShapeComponent>(CollisionComponentName);
    if (CollisionComponent)
    {
        // 계층 구조 설정
        CollisionComponent->SetupAttachment(RootComponent);

        // 충돌 설정
        CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
        CollisionComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
        CollisionComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
    }

    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));
    DisplayMesh->SetupAttachment(RootComponent);
    DisplayMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    DisplayMesh->SetCollisionResponseToAllChannels(ECR_Block);
    DisplayMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AGGFTriggerBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    BindOverlapEvents();
}

void AGGFTriggerBase::BindOverlapEvents()
{
    if(GetCollisionComponent())
    {
        GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCollisionComponentBeginOverlap);
        GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnCollisionComponentEndOverlap);
    }
}

void AGGFTriggerBase::UnbindOverlapEvents()
{
    if(GetCollisionComponent())
    {
        GetCollisionComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnCollisionComponentBeginOverlap);
        GetCollisionComponent()->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnCollisionComponentEndOverlap);
    }
}

void AGGFTriggerBase::OnCollisionComponentBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                                      AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                                      const FHitResult& SweepResult)
{
#if WITH_EDITOR
    if(bEnableLog)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherActor: %s"), *OtherActor->GetName())
#endif

    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        OnCollisionComponentBeginOverlapPawn(OverlappedComponent, OtherPawn, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    }
}

void AGGFTriggerBase::OnCollisionComponentEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
#if WITH_EDITOR
    if(bEnableLog)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherActor: %s"), *OtherActor->GetName())
#endif

    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        OnCollisionComponentEndOverlapPawn(OverlappedComponent, OtherPawn, OtherComp, OtherBodyIndex);
    }
}

void AGGFTriggerBase::OnCollisionComponentBeginOverlapPawn_Implementation(UPrimitiveComponent* OverlappedComponent,
    APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
#if WITH_EDITOR
    if(bEnableLog)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherPawn: %s"), *OtherPawn->GetName())
#endif
}

void AGGFTriggerBase::OnCollisionComponentEndOverlapPawn_Implementation(UPrimitiveComponent* OverlappedComponent,
    APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
#if WITH_EDITOR
    if(bEnableLog)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherPawn: %s"), *OtherPawn->GetName())
#endif
}
