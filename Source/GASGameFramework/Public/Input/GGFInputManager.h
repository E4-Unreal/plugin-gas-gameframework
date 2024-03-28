// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"

#include "GGFInputManager.generated.h"

class UGGFInputConfig;
/**
 * 향상된 입력 시스템에 입력 액션 바인딩 전용 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGGFInputManager : public UPawnComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TArray<TObjectPtr<UGGFInputConfig>> InputConfigs;

public:
    void BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);
};
