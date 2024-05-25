// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/GGFFirstPersonCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/GGFSpringArmComponent.h"

AGGFFirstPersonCharacter::AGGFFirstPersonCharacter(const FObjectInitializer& ObjectInitializer)
{
    /* 1인칭 */
    // 스프링 암
    SpringArm = CreateDefaultSubobject<UGGFSpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->SetRelativeLocation(FVector(0, 0, 70));
    SpringArm->SocketOffset = FVector::ZeroVector;
    SpringArm->TargetArmLength = 0;

    // 팔 스켈레탈 메시
    FirstPersonArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArms"));
    FirstPersonArms->SetupAttachment(SpringArm);
    FirstPersonArms->SetRelativeLocation(FVector(0, 0, -165.5f));
    FirstPersonArms->SetRelativeRotation(FRotator(0, -90, 0));
    FirstPersonArms->CastShadow = false;
    FirstPersonArms->SetOnlyOwnerSee(true);

    // 다리 스켈레탈 메시
    FirstPersonLegs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonLegs"));
    FirstPersonLegs->SetupAttachment(GetMesh());
    FirstPersonLegs->SetOnlyOwnerSee(true);

    // 카메라
    GameViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameViewCamera"));
    GameViewCamera->SetupAttachment(FirstPersonArms, "SOCKET_Camera");
    GameViewCamera->SetComponentTickEnabled(false);
    GameViewCamera->SetFieldOfView(120);

    /* 3인칭 */
    USkeletalMeshComponent* ThirdPersonSkeletalMesh = GetMesh();
    ThirdPersonSkeletalMesh->SetOwnerNoSee(true);
    ThirdPersonSkeletalMesh->bCastHiddenShadow = true;
    ThirdPersonSkeletalMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void AGGFFirstPersonCharacter::GetTarget_Implementation(FVector& Target)
{
    const UWorld* World = GetWorld();
    if(World == nullptr) return;

    // 카메라를 기준으로 라인 트레이스를 위한 위치 계산
    const FTransform& CameraTransform = GameViewCamera->GetComponentTransform();
    const FVector& TraceStart = CameraTransform.GetLocation();
    const FVector& TraceEnd = TraceStart + 100000.f * GameViewCamera->GetForwardVector();
    FHitResult HitResult;

    // 자기 자신 제외
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(this);

    // 라인 트레이스
    World->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECC_Visibility,
        CollisionQueryParams
        );

    Target = HitResult.bBlockingHit ? HitResult.Location : TraceEnd;
}
