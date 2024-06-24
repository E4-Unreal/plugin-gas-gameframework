// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGE_Heal.h"
#include "GGFGE_ContinuousHeal.generated.h"

/**
 * 힐 전용 게임플레이 이펙트로 일정 시간마다 체력을 회복합니다.
 * 횟수 제한이 존재합니다.
 */
UCLASS()
class GGFCOMBATSYSTEM_API UGGFGE_ContinuousHeal : public UGGFGE_Heal
{
    GENERATED_BODY()

public:
    UGGFGE_ContinuousHeal();
};
