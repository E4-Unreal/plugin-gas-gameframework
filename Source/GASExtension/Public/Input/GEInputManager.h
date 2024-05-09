// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GEInputManager.generated.h"

class UInputMappingContext;
class UGEInputConfig;

/**
 * 향상된 입력 시스템에 입력 액션 바인딩 전용 컴포넌트
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGEInputManager : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UGEInputConfig>> InputConfigs;

public:
    /* ActorComponent */
    virtual void BeginPlay() override;

    /* API */
    // ACharacter::SetupPlayerInputComponent에서 호출해주어야 합니다.
    void BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

private:
    void RegisterInputMappingContexts();
};
