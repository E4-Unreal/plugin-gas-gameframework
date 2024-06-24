// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFAimingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class GGFSHOOTERCORE_API UGGFAimingInterface : public UInterface
{
    GENERATED_BODY()
};

// TODO 상호작용에서도 사용할 수 있습니다. 나중에 통합 예정입니다.
/**
 * 대상이 바라보고 있는 목표 위치를 알아내기 위한 인터페이스입니다.
 */
class GGFSHOOTERCORE_API IGGFAimingInterface
{
    GENERATED_BODY()

public:
    // 대상이 바라보고 있는 목표 위치
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FVector GetTargetLocation() const;
};
