// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerState.h"
#include "Types/GGFTeamTypes.h"
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

protected:
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTeamInfo, BlueprintSetter = SetTeamInfo, Category = "State", Transient, ReplicatedUsing = OnRep_TeamInfo)
    FGGFTeamInfo TeamInfo;

public:
    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void BeginPlay() override;

    /* AbilitySystemInterface */

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    /* GenericTeamAgentInterface */

    virtual FGenericTeamId GetGenericTeamId() const override;
    virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGGFTeamInfo& GetTeamInfo() const { return TeamInfo; }

    /* Setter */

    UFUNCTION(BlueprintSetter)
    virtual void SetTeamInfo(const FGGFTeamInfo& NewTeamInfo);

protected:
    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_TeamInfo(const FGGFTeamInfo& OldTeamInfo);
};
