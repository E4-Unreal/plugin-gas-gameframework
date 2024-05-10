// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GEInputConfig.generated.h"

class UInputAction;
class UEnhancedInputComponent;

/**
 * 어빌리티 전용 입력 액션과 게임플레이 입력 태그 매핑 정보를 저장하는 데이터 에셋
 */
UCLASS(Abstract)
class GASEXTENSION_API UGEInputConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    void BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

protected:
    virtual void OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) { }
};
