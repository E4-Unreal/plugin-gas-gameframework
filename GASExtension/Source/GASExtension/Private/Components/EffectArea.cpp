// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EffectArea.h"

#include "FunctionLibraries/GEFunctionLibrary.h"


UEffectArea::UEffectArea()
{
    // 틱 활성화
    PrimaryComponentTick.bCanEverTick = true;
}

void UEffectArea::BeginPlay()
{
    Super::BeginPlay();

    // 게임 시작 시 이미 오버랩된 액터들 확인
    TArray<AActor*> OverlappingActors;
    Collider->GetOverlappingActors(OverlappingActors);

    // 오버랩된 액터 추가
    for (AActor* OtherActor : OverlappingActors)
    {
        AddOverlappedActor(OtherActor);
    }
}

void UEffectArea::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(UWorld* World = GetWorld())
    {
        // 오버랩된 액터에게 주기적으로 Effects 적용
        for (auto& [OverlappedActor, OverlappedTime] : OverlappedActors)
        {
            // 오버랩된 액터가 파괴된 경우
            if(OverlappedActor->IsActorBeingDestroyed())
            {
                OverlappedActors.Remove(OverlappedActor);
                continue;
            }

            // 오버랩된 시간 기록
            OverlappedTime += DeltaTime;

            // 오버랩된 기간이 Period보다 큰 경우
            if(OverlappedTime > Period)
            {
                ApplyEffectsToOverlappedActor(OverlappedActor);
                OverlappedTime -= Period;
            }
        }
    }
}

void UEffectArea::InjectDependencies(UPrimitiveComponent* InCollider)
{
    // null 검사
    if(InCollider == nullptr) return;

    // 초기화는 한 번만 진행
    if(bInitialized) return;
    bInitialized = true;

    // 의존성 주입
    Collider = InCollider;

    // 이벤트 바인딩
    Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap_Event);
    Collider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap_Event);
}

void UEffectArea::ApplyEffectsToOverlappedActor_Implementation(AActor* OtherActor)
{
    UGEFunctionLibrary::ApplyGameplayEffectsToTarget(EffectsToApply, GetOwner()->GetInstigator(), OtherActor);
}

void UEffectArea::AddOverlappedActor(AActor* OtherActor)
{
    // 오버랩된 시간을 기록합니다.
    if(UWorld* World = GetWorld())
    {
        OverlappedActors.Add(OtherActor, 0.f);
        ApplyEffectsToOverlappedActor(OtherActor);
    }
}

void UEffectArea::OnComponentBeginOverlap_Event(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AddOverlappedActor(OtherActor);
}

void UEffectArea::OnComponentEndOverlap_Event(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    OverlappedActors.Remove(OtherActor);
}
