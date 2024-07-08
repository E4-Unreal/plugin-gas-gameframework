// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFTriggerBase.h"

#include "Logging.h"
#include "Components/ShapeComponent.h"

FName AGGFTriggerBase::DefaultSceneName(TEXT("DefaultScene"));
FName AGGFTriggerBase::CollisionName(TEXT("Collision"));
FName AGGFTriggerBase::DisplayMeshName(TEXT("DisplayMesh"));

AGGFTriggerBase::AGGFTriggerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    /* DefaultScene */
    DefaultScene = CreateDefaultSubobject<USceneComponent>(DefaultSceneName);
    SetRootComponent(DefaultScene);

    /* Collision */
    Collision = CreateDefaultSubobject<UShapeComponent>(CollisionName);
    if (Collision)
    {
        // 계층 구조 설정
        Collision->SetupAttachment(RootComponent);

        // 충돌 설정
        Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        Collision->SetCollisionResponseToAllChannels(ECR_Overlap);
        Collision->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
        Collision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
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

bool AGGFTriggerBase::CheckOverlapCondition(AActor* OtherActor) const
{
    // 클래스 필터가 설정되지 않은 경우 모든 클래스 허용
    if(ClassFilters.IsEmpty()) return true;

    // 클래스 필터 검사
    for (auto ClassFilter : ClassFilters)
    {
        if(OtherActor->IsA(ClassFilter))
        {
            // 성공
            return true;
        }
    }

    // 실패
    return false;
}

void AGGFTriggerBase::BindOverlapEvents()
{
    if(GetCollision())
    {
        GetCollision()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::InternalOnCollisionBeginOverlap);
        GetCollision()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::InternalOnCollisionEndOverlap);
    }
}

void AGGFTriggerBase::UnbindOverlapEvents()
{
    if(GetCollision())
    {
        GetCollision()->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::InternalOnCollisionBeginOverlap);
        GetCollision()->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::InternalOnCollisionEndOverlap);
    }
}

void AGGFTriggerBase::InternalOnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 클래스 필터가 설정되지 않은 경우 모든 클래스 허용
    bool bSucceed = ClassFilters.IsEmpty();

    // 클래스 필터 적용
    for (auto ClassFilter : ClassFilters)
    {
        if(bSucceed) break;

        bSucceed = OtherActor->IsA(ClassFilter);
    }

    // 클래스 필터 결과 확인
    if(!bSucceed) return;

#if WITH_EDITOR
    if(bEnableLog)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherActor: %s"), *OtherActor->GetName())
#endif

    // 이벤트 호출
    OnCollisionBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AGGFTriggerBase::InternalOnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // 클래스 필터가 설정되지 않은 경우 모든 클래스 허용
    bool bSucceed = ClassFilters.IsEmpty();

    // 클래스 필터 적용
    for (auto ClassFilter : ClassFilters)
    {
        if(bSucceed) break;

        bSucceed = OtherActor->IsA(ClassFilter);
    }

    // 클래스 필터 결과 확인
    if(!bSucceed) return;

#if WITH_EDITOR
    if(bEnableLog)
        LOG_ACTOR_DETAIL(Log, TEXT("OtherActor: %s"), *OtherActor->GetName())
#endif

    // 이벤트 호출
    OnCollisionEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AGGFTriggerBase::OnCollisionBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
                                                             AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                             const FHitResult& SweepResult)
{

}

void AGGFTriggerBase::OnCollisionEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
