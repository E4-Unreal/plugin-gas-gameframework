// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GGFGameState.h"
#include "GameFramework/PlayerState.h"
#include "GGFPlayerState.generated.h"

/**
 * GASGameFramework 플러그인 전용 플레이어 스테이트
 */
UCLASS()
class GGFGAMESYSTEM_API AGGFPlayerState : public APlayerState,
    public IAbilitySystemInterface,
    public IGenericTeamAgentInterface
{
    GENERATED_BODY()

public:
    /* AbilitySystemInterface */

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    /* GenericTeamAgentInterface */

    virtual FGenericTeamId GetGenericTeamId() const override;
    virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;
};
