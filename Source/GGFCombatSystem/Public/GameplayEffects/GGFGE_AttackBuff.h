// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGE_Buff.h"
#include "GGFGE_AttackBuff.generated.h"

/**
 * 공격력 버프 전용 게임플레이 이펙트
 */
UCLASS()
class GGFCOMBATSYSTEM_API UGGFGE_AttackBuff : public UGGFGE_Buff
{
    GENERATED_BODY()

public:
    UGGFGE_AttackBuff();
};
