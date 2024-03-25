// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFAimingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API UGGFAimingInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 일반적으로 무기는 캐릭터가 조준하여 사용합니다.
 * 그러나 조준 정보가 필요없는 무기도 존재할 수 있는데 캐릭터가 이를 구분하는 것은 비효율적이라고 생각하였기 때문에 작성한 인터페이스입니다.
 */
class GASGAMEFRAMEWORK_API IGGFAimingInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void GetTarget(FVector& Target);
};
