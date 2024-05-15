// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFCameraInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class GGFEQUIPMENTSYSTEM_API UGGFCameraInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * ADS 상태에서 FOV 및 카메라 위치 조정을 위한 데이터 인터페이스입니다.
 * 캐릭터와 무기에 각각 구현하여 캐릭터 값을 기본 값으로 사용하고 ADS 상태에서는 무기의 값을 사용합니다.
 */
class GGFEQUIPMENTSYSTEM_API IGGFCameraInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float GetFieldOfView() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float GetInterpSpeed() const;
};
