// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/GEDamageableAbilitySystem.h"

#include "GEGameplayTags.h"
#include "Attributes/GEHealthAttributes.h"

UGEDamageableAbilitySystem::UGEDamageableAbilitySystem()
{
    // 체력 어트리뷰트 추가
    DefaultAttributes.AddUnique(UGEHealthAttributes::StaticClass());
}

bool UGEDamageableAbilitySystem::IsDead() const
{
    return HasMatchingGameplayTag(GEGameplayTags::State::Dead);
}

void UGEDamageableAbilitySystem::ServerInitializeComponent_Implementation()
{
    Super::ServerInitializeComponent_Implementation();

    // 죽음 이벤트 바인딩
    BindDeadEvent();
}

void UGEDamageableAbilitySystem::OnDead_Implementation()
{
    // 태그 설정
    FGameplayTag DeadTag = GEGameplayTags::State::Dead;

    // 서버 액터에 태그 부착
    AddLooseGameplayTag(DeadTag);

    // 클라이언트 액터에 태그 부착
    AddReplicatedLooseGameplayTag(DeadTag);
}

void UGEDamageableAbilitySystem::BindDeadEvent()
{
    FOnGameplayAttributeValueChange& Delegate = GetGameplayAttributeValueChangeDelegate(UGEHealthAttributes::GetHealthAttribute());
    Delegate.AddLambda([this](const FOnAttributeChangeData& OnAttributeChangeData)
    {
        // 중복 호출 방지 및 죽음 판정
        if(!IsDead() && FMath::IsNearlyZero(OnAttributeChangeData.NewValue))
        {
            // 죽음 처리를 위한 이벤트 메서드 호출
            OnDead();
        }
    });
}
