// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GGFDataTypes.generated.h"

/**
 * ID 목록을 저장하기 위해 범용적으로 사용되는 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFIDContainer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    TArray<int32> List;
};
