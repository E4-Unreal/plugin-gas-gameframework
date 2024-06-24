// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerBox.h"

#include "Logging.h"
#include "Components/BoxComponent.h"

AGGFTriggerBox::AGGFTriggerBox(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* Default Scene */

    // 서브 오브젝트 생성
    DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
    SetRootComponent(DefaultScene);

    /* Trigger Box */

    // 서브 오브젝트 생성
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);

    // 충돌 설정
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    TriggerBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

    // 기본 설정
    TriggerBox->InitBoxExtent(FVector(100, 100, 100));

    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));
    DisplayMesh->SetupAttachment(RootComponent);

    // 충돌 설정
    DisplayMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    DisplayMesh->SetCollisionResponseToAllChannels(ECR_Block);
    DisplayMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AGGFTriggerBox::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    BindTriggerBoxEvents();
}

void AGGFTriggerBox::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // 트리거 박스의 피벗 위치를 정중앙에서 정하단으로 변경
    RefreshTriggerBox();
}

void AGGFTriggerBox::BindTriggerBoxEvents()
{
    if(!bServerOnly || HasAuthority())
    {
        // 트리거 이벤트 바인딩
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTriggerBoxBeginOverlap);
        TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnTriggerBoxEndOverlap);
    }
}

void AGGFTriggerBox::UnBindTriggerBoxEvents()
{
    if(!bServerOnly || HasAuthority())
    {
        // 트리거 이벤트 바인딩
        TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBoxBeginOverlap);
        TriggerBox->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnTriggerBoxEndOverlap);
    }
}

void AGGFTriggerBox::RefreshTriggerBox()
{
    const FVector ScaledTriggerBoxExtent = TriggerBox->GetScaledBoxExtent();
    TriggerBox->SetRelativeLocation(FVector(0, 0, ScaledTriggerBoxExtent.Z));
}

void AGGFTriggerBox::OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
#if WITH_EDITOR
    if(bEnableDebug)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherActor: %s"), *OtherActor->GetName())
#endif

    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        OnTriggerBoxBeginOverlapPawn(OverlappedComponent, OtherPawn, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    }
}

void AGGFTriggerBox::OnTriggerBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
#if WITH_EDITOR
    if(bEnableDebug)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherActor: %s"), *OtherActor->GetName())
#endif

    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        OnTriggerBoxEndOverlapPawn(OverlappedComponent, OtherPawn, OtherComp, OtherBodyIndex);
    }
}

void AGGFTriggerBox::OnTriggerBoxBeginOverlapPawn_Implementation(UPrimitiveComponent* OverlappedComponent,
    APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
#if WITH_EDITOR
    if(bEnableDebug)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherPawn: %s"), *OtherPawn->GetName())
#endif
}

void AGGFTriggerBox::OnTriggerBoxEndOverlapPawn_Implementation(UPrimitiveComponent* OverlappedComponent,
    APawn* OtherPawn, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
#if WITH_EDITOR
    if(bEnableDebug)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherPawn: %s"), *OtherPawn->GetName())
#endif
}
