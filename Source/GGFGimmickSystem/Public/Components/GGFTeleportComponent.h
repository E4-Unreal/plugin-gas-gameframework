﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "Components/ActorComponent.h"
#include "GGFTeleportComponent.generated.h"

/**
 * 텔레포트 기능은 자주 사용되는 기능이므로 액터 컴포넌트로 작성하였습니다.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFGIMMICKSYSTEM_API UGGFTeleportComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    // 순간이동 목표
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config")
    TObjectPtr<AActor> Target;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseYaw = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUsePitch = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseRoll = false;

    // 텔레포트 입장 전용 게임플레이 큐 태그
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayCueTag TeleportInCueTag;

    // 텔레포트 퇴장 전용 게임플레이 큐 태그
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayCueTag TeleportOutCueTag;

public:
    UGGFTeleportComponent();

    /* API */

    // Source를 Target으로 순간이동
    UFUNCTION(BlueprintCallable)
    virtual void Teleport(AActor* ActorToTeleport, AActor* TargetToTeleport = nullptr);

protected:
    /* 메서드 */

    // InTarget에 CueTag 스폰
    UFUNCTION(BlueprintCallable)
    virtual void HandleGameplayCue(AActor* ActorToTeleport, AActor* TargetToHandle, const FGameplayCueTag CueTag);
};