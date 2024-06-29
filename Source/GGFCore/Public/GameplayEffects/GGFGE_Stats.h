// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGameplayEffect.h"
#include "GGFGE_Stats.generated.h"

/**
 * 스탯 전용 게임플레이 이펙트 클래스입니다.
 */
UCLASS()
class GGFCORE_API UGGFGE_Stats : public UGGFGameplayEffect
{
    GENERATED_BODY()

protected:
    DEFINE_STAT_MODIFIER_PTR(Attack);
    DEFINE_STAT_MODIFIER_PTR(Defense);
    DEFINE_STAT_MODIFIER_PTR(MoveSpeed);
    DEFINE_STAT_MODIFIER_PTR(AttackSpeed);
    DEFINE_STAT_MODIFIER_PTR(AbilityHaste);

public:
    UGGFGE_Stats();
};
