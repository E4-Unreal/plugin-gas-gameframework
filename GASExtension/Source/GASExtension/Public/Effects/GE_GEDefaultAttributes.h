// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_GEDefaultAttributes.generated.h"

/**
 * AttributeSet 초기화 전용 GameplayEffect 예시입니다.
 * GEAbilitySystemBase에서는 GEStaminaAttributes가 기본 AttributeSet으로 설정되어 있기 때문에 이를 기준으로 작성되었습니다.
 */
UCLASS()
class GASEXTENSION_API UGE_GEDefaultAttributes : public UGameplayEffect
{
    GENERATED_BODY()

public:
    UGE_GEDefaultAttributes();
};
