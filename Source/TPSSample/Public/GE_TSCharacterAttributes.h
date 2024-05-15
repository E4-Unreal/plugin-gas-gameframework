// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_TSCharacterAttributes.generated.h"

/**
 * 캐릭터 기본 특성 초기화 전용 GameplayEffect 클래스입니다.
 * 블루프린트 에셋 생성 후 설정하여 사용하시면 됩니다.
 */
UCLASS()
class TPSSAMPLE_API UGE_TSCharacterAttributes : public UGameplayEffect
{
    GENERATED_BODY()

public:
    UGE_TSCharacterAttributes();
};
