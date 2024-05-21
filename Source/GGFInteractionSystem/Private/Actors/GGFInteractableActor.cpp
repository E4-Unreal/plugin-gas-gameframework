// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "GGFInteractionGameplayTags.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

FName AGGFInteractableActor::InteractionWidgetName(TEXT("InteractionWidget"));

AGGFInteractableActor::AGGFInteractableActor()
    : InteractableAreaMargin(FVector(100, 100, 50))
{
    /* InteractableArea */
    // 서브 오브젝트 생성
    InteractableArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractableArea"));

    // 계층 설정
    InteractableArea->SetupAttachment(RootComponent);

    // 충돌 설정
    InteractableArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractableArea->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractableArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    /* InteractionWidget */
    // 서브 오브젝트 생성
    InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(InteractionWidgetName);

    // 계층 설정
    InteractionWidget->SetupAttachment(RootComponent);

    // 충돌 설정
    InteractionWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 초기화
    InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
    InteractionWidget->SetDrawAtDesiredSize(true);
    InteractionWidget->SetVisibility(false);

    /* DisplayMesh */
    // 서브 오브젝트 생성
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));

    // 계층 설정
    DisplayMesh->SetupAttachment(RootComponent);
}

void AGGFInteractableActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 오버랩 이벤트 바인딩
    InteractableArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractableAreaBeginOverlap);
    InteractableArea->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractableAreaEndOverlap);

    // 위치 조정
    AdjustToDisplayMesh();
}

void AGGFInteractableActor::OnInteractableAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 폰만 감지
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if(OtherPawn == nullptr) return;

    // 플레이어 여부 확인
    if(OtherPawn->IsPlayerControlled())
    {
        OnPlayerPawnBeginOverlap(OtherPawn);

        // 로컬 플레이어 여부 확인
        if(OtherPawn->IsLocallyControlled())
        {
            OnLocalPlayerPawnBeginOverlap(OtherPawn);
        }
    }
}

void AGGFInteractableActor::OnInteractableAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // 폰만 감지
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if(OtherPawn == nullptr) return;

    // 플레이어 여부 확인
    if(OtherPawn->IsPlayerControlled())
    {
        OnPlayerPawnEndOverlap(OtherPawn);

        // 로컬 플레이어 여부 확인
        if(OtherPawn->IsLocallyControlled())
        {
            OnLocalPlayerPawnEndOverlap(OtherPawn);
        }
    }
}

void AGGFInteractableActor::OnPlayerPawnBeginOverlap_Implementation(APawn* PlayerPawn)
{
    // Interactable 태그 부여
    if(UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PlayerPawn))
    {
        AbilitySystem->AddLooseGameplayTag(GGFGameplayTags::State::Interactable);
    }
}

void AGGFInteractableActor::OnPlayerPawnEndOverlap_Implementation(APawn* PlayerPawn)
{
    // Interactable 태그 제거
    if(UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PlayerPawn))
    {
        AbilitySystem->RemoveLooseGameplayTag(GGFGameplayTags::State::Interactable);
    }
}

void AGGFInteractableActor::OnLocalPlayerPawnBeginOverlap_Implementation(APawn* LocalPlayerPawn)
{
    // 외곽선 활성화
    EnableOutline(true);
}

void AGGFInteractableActor::OnLocalPlayerPawnEndOverlap_Implementation(APawn* LocalPlayerPawn)
{
    // 외곽선 비활성화
    EnableOutline(false);
}

void AGGFInteractableActor::EnableOutline_Implementation(bool bEnable)
{
    // DisplayMesh 외곽선 활성화
    DisplayMesh->SetRenderCustomDepth(bEnable);

    // DisplayMesh에 부착된 모든 하위 메시 외곽선 활성화
    TArray<USceneComponent*> SceneComponents;
    DisplayMesh->GetChildrenComponents(true, SceneComponents);

    for (USceneComponent* SceneComponent : SceneComponents)
    {
        if(UMeshComponent* MeshComponent = Cast<UMeshComponent>(SceneComponent))
        {
            MeshComponent->SetRenderCustomDepth(bEnable);
        }
    }
}

void AGGFInteractableActor::ActivateInteractionWidget_Implementation(bool bActivate)
{
    InteractionWidget->SetVisibility(bActivate);
}

void AGGFInteractableActor::AdjustToDisplayMesh_Implementation()
{
    if(DisplayMesh->GetStaticMesh())
    {
        // Bound 가져오기
        FVector BoxExtent = DisplayMesh->GetStaticMesh()->GetBoundingBox().GetExtent() * DisplayMesh->GetRelativeScale3D();

        // 상호작용 가능 범위 재설정
        InteractableArea->SetBoxExtent(BoxExtent + InteractableAreaMargin);
        InteractableArea->SetRelativeLocation(FVector(0, 0, InteractableArea->GetScaledBoxExtent().Z));

        // 위젯 위치 조정
        InteractionWidget->SetRelativeLocation(FVector(0, 0, 2 * BoxExtent.Z));
    }
    else
    {
        // 초기화
        InteractableArea->SetBoxExtent(FVector::ZeroVector);
        InteractableArea->SetRelativeLocation(FVector::ZeroVector);
        InteractionWidget->SetRelativeLocation(FVector::ZeroVector);
    }
}

bool AGGFInteractableActor::Activate_Implementation(AActor* OtherActor)
{
    // 상위 클래스에서 문제가 발생한 경우
    if(!Super::Activate_Implementation(OtherActor)) return false;

    // 로컬 플레이어만 감지
    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        if(OtherPawn->Controller && OtherPawn->Controller->IsLocalPlayerController())
        {
            ActivateInteractionWidget(true);
            return true;
        }
    }

    return false;
}

bool AGGFInteractableActor::Deactivate_Implementation(AActor* OtherActor)
{
    // 상위 클래스에서 문제가 발생한 경우
    if(!Super::Deactivate_Implementation(OtherActor)) return false;

    // 로컬 플레이어만 감지
    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        if(OtherPawn->Controller && OtherPawn->Controller->IsLocalPlayerController())
        {
            ActivateInteractionWidget(false);
            return true;
        }
    }

    return false;
}
