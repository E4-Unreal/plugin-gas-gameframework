// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFDataInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFDATASYSTEM_API UGGFDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 데이터 설정 및 관리를 위한 인터페이스
 */
class GGFDATASYSTEM_API IGGFDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetID();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetID(int32 NewID);
};
