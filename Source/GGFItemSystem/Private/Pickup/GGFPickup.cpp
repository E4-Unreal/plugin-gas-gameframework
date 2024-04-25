// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup/GGFPickup.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Pickup/GGFItemConfig_Pickup.h"
#include "Pickup/GGFPickupWidget.h"

AGGFPickup::AGGFPickup(const FObjectInitializer& ObjectInitializer)
{
    // 트리거 박스 (Pawn만 오버랩 허용)
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    SetRootComponent(TriggerBox);
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerBox->SetGenerateOverlapEvents(true);

    // 스태틱 메시
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    DisplayMesh->SetupAttachment(RootComponent);
    DisplayMesh->SetCollisionProfileName("NoCollision");
    DisplayMesh->SetGenerateOverlapEvents(false);

    // 위젯
    Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
    Widget->SetupAttachment(RootComponent);
    Widget->SetGenerateOverlapEvents(false);
    Widget->SetWidgetSpace(EWidgetSpace::Screen);
    Widget->SetDrawAtDesiredSize(true);
    Widget->SetVisibility(false);
}

void AGGFPickup::BeginPlay()
{
    Super::BeginPlay();

    if(UGGFPickupWidget* PickupWidget = Cast<UGGFPickupWidget>(Widget->GetWidget()))
    {
        PickupWidget->SetPickup(this);
    }
}

void AGGFPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    // OtherActor가 Pawn 클래스인지 확인
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if(OtherPawn == nullptr) return;

    // 로컬 플레이어인지 확인
    if(!OtherPawn->IsLocallyControlled()) return;

    // 위젯 컴포넌트 활성화
    SetWidgetVisibility(true);

    // 외곽선 활성화
    SetOutlineVisibility(true);
}

void AGGFPickup::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    // OtherActor가 Pawn 클래스인지 확인
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if(OtherPawn == nullptr) return;

    // 로컬 플레이어인지 확인
    if(!OtherPawn->IsLocallyControlled()) return;

    // 위젯 컴포넌트 비활성화
    SetWidgetVisibility(false);

    // 외곽선 비활성화
    SetOutlineVisibility(false);
}

void AGGFPickup::InitFromItemDefinition(UGGFItemDefinition* InItemDefinition)
{
    // 초기화를 위한 데이터 에셋 캐싱
    ItemDefinition = InItemDefinition;

    // 초기화
    if(ItemDefinition)
    {
        UGGFItemConfig_Pickup* NewItemConfig = Cast<UGGFItemConfig_Pickup>(ItemDefinition->FindConfigByClass(UGGFItemConfig_Pickup::StaticClass()));
        InitFromItemConfig(NewItemConfig);
    }
    else
    {
        Reset();
    }
}

void AGGFPickup::InitFromItemConfig(UGGFItemConfig_Pickup* InItemConfig)
{
    // 초기화를 위한 데이터 에셋 캐싱
    ItemConfig = InItemConfig;

    // 초기화
    if(ItemConfig)
    {
        InitFromPickupData(ItemConfig->GetPickupData());
    }
    else
    {
        Reset();
    }
}

void AGGFPickup::InitFromPickupData(const FGGFPickupData& InPickupData)
{
    // 유효성 검사
    if(InPickupData.IsValid())
    {
        // 메시 설정 및 위치 조정
        DisplayMesh->SetStaticMesh(InPickupData.StaticMesh);
        DisplayMesh->SetRelativeTransform(InPickupData.Offset);
        switch (InPickupData.Pivot)
        {
        case EGGFStaticMeshPivot::Center:
            DisplayMesh->AddRelativeLocation(FVector(0, 0, GetDisplayMesh()->Bounds.BoxExtent.Z));
            break;
        case EGGFStaticMeshPivot::Bottom:
            break;
        case EGGFStaticMeshPivot::Top:
            DisplayMesh->AddRelativeLocation(FVector(0, 0, 2 * GetDisplayMesh()->Bounds.BoxExtent.Z));
            break;
        default:
            break;
        }

        // 콜리전 박스 설정
        TriggerBox->SetBoxExtent(DisplayMesh->GetStaticMesh()->GetBoundingBox().Max * DisplayMesh->GetRelativeScale3D() + FVector(100, 100, 100));

        // 위젯 위치 조정
        Widget->AddRelativeLocation(FVector(0, 0, GetDisplayMesh()->Bounds.BoxExtent.Z));

        // 수량 설정
        Amount = InPickupData.DefaultAmount;

        // 위치 설정
        SetLandingPosition();

        // 초기화 플래그 설정
        bIsInitialized = true;
    }
    else
    {
        Reset();
    }

    // 이벤트 호출
    OnUpdated.Broadcast();
}

void AGGFPickup::Reset()
{
    Super::Reset();

    // 메시 초기화
    DisplayMesh->SetStaticMesh(nullptr);
    DisplayMesh->SetRelativeTransform(FTransform::Identity);

    // 수량 초기화
    Amount = 0;

    // 콜리전 박스 초기화
    TriggerBox->InitBoxExtent(FVector::ZeroVector);

    // 초기화 플래그 설정
    bIsInitialized = false;
}

void AGGFPickup::SetLandingPosition()
{
    if(UWorld* World = GetWorld())
    {
        // -Z축에서 가장 근접한 오브젝트 위로 이동
        FHitResult HitResult;
        FVector Start = GetActorLocation();
        FVector End = Start - GetActorUpVector() * 1000;
        FCollisionQueryParams CollisionQueryParams;
        CollisionQueryParams.AddIgnoredActor(this);
        World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionQueryParams);

        if(HitResult.bBlockingHit) SetActorLocation(HitResult.ImpactPoint);
    }
}

void AGGFPickup::SetWidgetVisibility(bool bEnable)
{
    Widget->SetVisibility(bEnable);
}

void AGGFPickup::SetOutlineVisibility(bool bEnable)
{
    DisplayMesh->SetRenderCustomDepth(bEnable);
}

void AGGFPickup::SetAmount(int32 InAmount)
{
    Amount = InAmount;

    if(Amount <= 0) Destroy();

    // 이벤트 호출
    OnUpdated.Broadcast();
}
