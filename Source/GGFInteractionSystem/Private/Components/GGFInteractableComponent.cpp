// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFInteractableComponent.h"

#include "Logging.h"
#include "KismetTraceUtils.h"
#include "Components/GGFInteractionManager.h"
#include "Components/ShapeComponent.h"
#include "Interfaces/GGFInteractionInfoWidgetInterface.h"

UGGFInteractableComponent::UGGFInteractableComponent()
{
    /* 기본 설정 */

    bWantsInitializeComponent = true;
    PrimaryComponentTick.bCanEverTick = true;
    SetWidgetSpace(EWidgetSpace::Screen);
    SetDrawAtDesiredSize(true);
    BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);

    /* 블루프린트 에셋 기본 할당 */

    // GASGameFramework 플러그인
    static ConstructorHelpers::FClassFinder<UUserWidget> InteractionInfoWidgetClassFinder(TEXT("/GASGameFramework/Objects/Interactable/WBP_InteractionInfo_Sample.WBP_InteractionInfo_Sample_C"));
    if (InteractionInfoWidgetClassFinder.Succeeded())
    {
        SetWidgetClass(InteractionInfoWidgetClassFinder.Class);
    }
}

void UGGFInteractableComponent::InitializeComponent()
{
    Super::InitializeComponent();

    SetVisibility(false);
    EnableOutline(false);
}

void UGGFInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    for (auto OverlappedPawn : OverlappedPawns)
    {
        bool bTraceResult = TracePawnCamera(OverlappedPawn, DeltaTime);
        SetInteractionManager(OverlappedPawn, bTraceResult);
    }
}

void UGGFInteractableComponent::DestroyComponent(bool bPromoteChildren)
{
    for (auto OverlappedPawn : OverlappedPawns)
    {
        SetInteractionManager(OverlappedPawn, false);
    }

    Super::DestroyComponent(bPromoteChildren);
}

void UGGFInteractableComponent::InitWidget()
{
    Super::InitWidget();

    RefreshWidget();
}

void UGGFInteractableComponent::Init(UShapeComponent* InInteractableArea, UMeshComponent* InOutlineTarget)
{
    /* InteractableArea */

    InteractableArea = InInteractableArea;
    InteractableArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnInteractableAreaBeginOverlap);
    InteractableArea->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnInteractableAreaEndOverlap);

    /* OutlineTarget */

    // 초기화
    OutlineTargets.Reset();
    OutlineTargets.Emplace(InOutlineTarget);

    TArray<USceneComponent*> ChildrenComponents;
    InOutlineTarget->GetChildrenComponents(true, ChildrenComponents);

    for (USceneComponent* ChildComponent : ChildrenComponents)
    {
        if(UMeshComponent* ChildMeshComponent = Cast<UMeshComponent>(ChildComponent))
        {
            OutlineTargets.Emplace(ChildMeshComponent);
        }
    }

    OutlineTargets.Shrink();
}

void UGGFInteractableComponent::TryInteract(APawn* OtherPawn)
{
    if(OtherPawn == nullptr) return;

#if WITH_EDITOR
    LOG_ACTOR_COMPONENT_DETAIL(Log, TEXT("%s TryInteract"), *OtherPawn->GetName())
#endif

    if(CanInteract(OtherPawn))
    {
        OnPawnInteract.Broadcast(OtherPawn);

        if(OtherPawn->IsPlayerControlled() && OtherPawn->IsLocallyControlled())
        {
            OnLocalPawnInteract.Broadcast(OtherPawn);
        }
    }
}

void UGGFInteractableComponent::RefreshWidget()
{
    if(GetWidget() && GetWidget()->Implements<UGGFInteractionInfoWidgetInterface>())
    {
        IGGFInteractionInfoWidgetInterface::Execute_SetDisplayName(GetWidget(), FText::FromName(DisplayName));
        IGGFInteractionInfoWidgetInterface::Execute_SetInteractionInfo(GetWidget(), FText::FromString(InteractionInfo));
    }
}

void UGGFInteractableComponent::OnInteractableAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                               AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                               const FHitResult& SweepResult)
{
    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        AddOverlappedPawn(OtherPawn);
    }
}

void UGGFInteractableComponent::OnInteractableAreaEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(APawn* OtherPawn = Cast<APawn>(OtherActor))
    {
        RemoveOverlappedPawn(OtherPawn);
    }
}

void UGGFInteractableComponent::SetInteractionManager(APawn* Target, bool bTraceResult)
{
    auto InteractionManager = Target->GetComponentByClass<UGGFInteractionManager>();
    InteractionManager->SetInteractableActor(GetOwner(), bTraceResult);

    if(Target->IsPlayerControlled() && Target->IsLocallyControlled())
    {
        SetVisibility(bTraceResult);
    }
}

void UGGFInteractableComponent::AddOverlappedPawn(APawn* NewPawn)
{
    if(NewPawn == nullptr) return;

    if(auto InteractionManager = NewPawn->GetComponentByClass<UGGFInteractionManager>())
    {
        // 오버랩된 폰 목록에 추가
        OverlappedPawns.Emplace(NewPawn);

        // 이벤트 호출
        OnPawnBeginOverlap.Broadcast(NewPawn);

        if(NewPawn->IsPlayerControlled() && NewPawn->IsLocallyControlled())
        {
            // 외곽선 효과 적용
            EnableOutline(true);

            // 이벤트 호출
            OnLocalPawnBeginOverlap.Broadcast(NewPawn);
        }
    }
}

void UGGFInteractableComponent::RemoveOverlappedPawn(APawn* OldPawn)
{
    // 입력 유효성 검사
    if(OldPawn == nullptr) return;

    // 오버랩된 폰 목록에 존재하는지 확인
    if(!OverlappedPawns.Contains(OldPawn)) return;

    // 오버랩된 폰 목록에서 제거
    OverlappedPawns.RemoveSwap(OldPawn);

    // 이벤트 호출
    OnPawnEndOverlap.Broadcast(OldPawn);

    if(OldPawn->IsPlayerControlled() && OldPawn->IsLocallyControlled())
    {
        // 외곽선 효과 적용 해제
        EnableOutline(false);

        // 이벤트 호출
        OnLocalPawnEndOverlap.Broadcast(OldPawn);
    }

    SetInteractionManager(OldPawn, false);
}

void UGGFInteractableComponent::EnableOutline(bool bEnable)
{
    for (auto OutlineTarget : OutlineTargets)
    {
        OutlineTarget->SetRenderCustomDepth(bEnable);
    }
}

bool UGGFInteractableComponent::TracePawnCamera(APawn* Target, float DeltaTime)
{
    // 유효성 검사
    if(!Target) return false;

    // 멀티 라인 트레이스를 위한 변수 설정
    FMinimalViewInfo ViewInfo;
    Target->CalcCamera(DeltaTime, ViewInfo);
    float Offset = (Target->GetActorLocation() - ViewInfo.Location).Size();
    const FVector TraceStart = ViewInfo.Location + Offset * ViewInfo.Rotation.Vector();
    const FVector TraceEnd = TraceStart + MaxDistance * ViewInfo.Rotation.Vector();
    TArray<FHitResult> OutHits;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(Target);

    // 멀티 라인 트레이스
    GetWorld()->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SphereRadius), CollisionQueryParams);

#if WITH_EDITOR
    // 디버그 시각화
    if(bShowDebug)
    {
        bool bHit = OutHits.Num() > 0;
        DrawDebugSphereTraceMulti(GetWorld(), TraceStart, TraceEnd, SphereRadius, EDrawDebugTrace::ForOneFrame, bHit, OutHits, FLinearColor::Red, FLinearColor::Green, 1);
    }
#endif

    // 상호작용 가능한 오브젝트 탐색
    for (const FHitResult& OutHit : OutHits)
    {
        // Owner와 관련된 액터인 경우 추가 검사 진행
        // 무기나 장비 등으로 인해 시야를 가리는 형상 방지
        if(OutHit.GetActor()->GetOwner() == Target) continue;

        // 다른 플레이어 폰인 경우 추가 검사 진행
        if(APawn* OtherPawn = Cast<APawn>(OutHit.GetActor()))
        {
            if(OtherPawn->IsPlayerControlled()) continue;
        }

        // 다른 플레이어 캐릭터가 소유권을 가진 액터인 경우 추가 검사 진행
        if(APawn* OtherPawnOwner = Cast<APawn>(OutHit.GetActor()->GetOwner()))
        {
            if(OtherPawnOwner->IsPlayerControlled()) continue;
        }

        // 상호작용 가능
        if(OutHit.GetActor() == GetOwner())
        {
            return true;
        }

        break;
    }

    return false;
}
