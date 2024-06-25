// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFTeamInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFCORE_API UGGFTeamInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 팀 구분을 위한 인터페이스
 */
class GGFCORE_API IGGFTeamInterface
{
    GENERATED_BODY()

public:
    static const uint8 NoTeam;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    uint8 GetTeamID() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTeamID(uint8 NewTeamID);
};
