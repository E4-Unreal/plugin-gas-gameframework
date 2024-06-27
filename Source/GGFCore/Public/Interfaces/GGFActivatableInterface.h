// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GGFActivatableInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class GGFCORE_API UGGFActivatableInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 액터 활성화 혹은 비활성화 이벤트 호출을 위한 인터페이스
 */
class GGFCORE_API IGGFActivatableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool Activate(AActor* InstigatorActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool Deactivate(AActor* InstigatorActor);
};
