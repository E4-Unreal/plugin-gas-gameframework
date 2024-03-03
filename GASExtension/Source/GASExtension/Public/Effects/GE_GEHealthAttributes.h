// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_GEHealthAttributes.generated.h"

/**
 * GEHealthAttributes 초기화 전용 GameplayEffect입니다.
 */
UCLASS()
class GASEXTENSION_API UGE_GEHealthAttributes : public UGameplayEffect
{
    GENERATED_BODY()

public:
    UGE_GEHealthAttributes();
};
