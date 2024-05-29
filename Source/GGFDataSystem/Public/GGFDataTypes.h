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

/**
 * TMap<KeyID, TArray<ValueID>>
 */
USTRUCT(Atomic, BlueprintType)
struct FGGFIDMapContainer
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    TMap<int32, FGGFIDContainer> Map;

    /* 연산자 오버로딩 */

    FORCEINLINE FGGFIDContainer& operator[](int32 KeyID) { return Map[KeyID]; }
    FORCEINLINE const FGGFIDContainer& operator[](int32 KeyID) const { return Map[KeyID]; }

    /* TMap */

    FORCEINLINE bool Contains(int32 KeyID) const { return Map.Contains(KeyID); }

    FORCEINLINE void Emplace(int32 KeyID, int32 ValueID)
    {
        if(Map.Contains(KeyID))
        {
            // KeyID가 이미 등록된 경우
            Map[KeyID].List.Emplace(ValueID);
        }
        else
        {
            // 처음으로 KeyID를 등록하는 경우
            FGGFIDContainer NewIDContainer;
            NewIDContainer.List.Emplace(ValueID);
            Map.Emplace(KeyID, NewIDContainer);
        }
    }

    FORCEINLINE void Emplace(int32 KeyID, const TArray<int32>& ValueIDList)
    {
        FGGFIDContainer NewContainer;
        NewContainer.List = ValueIDList;
        Map.Emplace(KeyID, NewContainer);
    }
};
