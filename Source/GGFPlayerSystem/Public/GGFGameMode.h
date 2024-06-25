// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Interfaces/GGFGameModeInterface.h"
#include "GGFGameMode.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FGGFPlayerControllerList
{
    GENERATED_BODY()

    static const TArray<APlayerController*> EmptyList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<APlayerController*> List;
};

/**
 * GASGameFramework 플러그인 전용 게임 모드
 */
UCLASS()
class GGFPLAYERSYSTEM_API AGGFGameMode : public AGameMode, public IGGFGameModeInterface
{
    GENERATED_BODY()

protected:
    // true 설정 시 모든 플레이어는 동일한 팀으로 취급됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAllPlayerSameTeam = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<uint8, FGGFPlayerControllerList> TeamMap;

public:
    AGGFGameMode();

    /* GameMode */

    virtual void PostLogin(APlayerController* NewPlayer) override;

    /* API */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetViewTargetToPreviousPlayer(APlayerController* PlayerController);

    // 같은 팀 플레이어 화면 관전
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetViewTargetToNextPlayer(APlayerController* PlayerController);

    UFUNCTION(BlueprintCallable)
    const TArray<APlayerController*>& GetTeamListByTeamID(int32 TeamID) const;

    UFUNCTION(BlueprintCallable)
    const TArray<APlayerController*>& GetTeamListByPlayerController(APlayerController* PlayerController) const;
};
