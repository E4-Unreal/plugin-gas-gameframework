// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/GGFEffectAreaComponent.h"

#include "AbilitySystemGlobals.h"
#include "GGFBlueprintFunctionLibrary.h"

UGGFEffectAreaComponent::UGGFEffectAreaComponent()
{
    // 틱 활성화
    PrimaryComponentTick.bCanEverTick = true;
}

void UGGFEffectAreaComponent::BeginPlay()
{
    Super::BeginPlay();

    // 게임 시작 시 이미 오버랩된 액터들 확인
    TArray<AActor*> OverlappingActors;
    EffectArea->GetOverlappingActors(OverlappingActors);

    // 오버랩된 액터 추가
    for (AActor* OtherActor : OverlappingActors)
    {
        AddOverlappedActor(OtherActor);
    }
}

void UGGFEffectAreaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
                ApplyEffectsToOverlappedActor(OverlappedActor.Get());
                OverlappedTime -= Period;
            }
        }
    }
}

void UGGFEffectAreaComponent::Init(UPrimitiveComponent* InEffectArea)
{
    // 입력 유효성 검사
    if(InEffectArea == nullptr) return;

    // 중복 호출 방지
    if(EffectArea) return;
    EffectArea = InEffectArea;

    // 이벤트 바인딩
    EffectArea->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEffectAreaBeginOverlap);
    EffectArea->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEffectAreaEndOverlap);
}

void UGGFEffectAreaComponent::ApplyEffectsToOverlappedActor_Implementation(AActor* OtherActor)
{
    UGGFBlueprintFunctionLibrary::ApplyGameplayEffectsToTarget(GetOwner(), OtherActor, EffectsToApply);
}

void UGGFEffectAreaComponent::AddOverlappedActor(AActor* OtherActor)
{
    // 오버랩 즉시 이펙트를 적용합니다.
    if(UWorld* World = GetWorld())
    {
        OverlappedActors.Add(OtherActor, 0.f);
        ApplyEffectsToOverlappedActor(OtherActor);
    }
}

void UGGFEffectAreaComponent::OnEffectAreaBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    AddOverlappedActor(OtherActor);
}

void UGGFEffectAreaComponent::OnEffectAreaEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    OverlappedActors.Remove(OtherActor);
}
