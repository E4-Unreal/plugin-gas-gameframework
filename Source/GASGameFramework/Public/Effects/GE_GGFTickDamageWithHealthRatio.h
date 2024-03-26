// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_GGFTickDamageWithHealthRatio.generated.h"

/**
 * GGFHealthAttributes에 데미지를 가하기 위한 GameplayEffect 기저 클래스입니다.
 * 테스트 혹은 블루프린트 설정을 편하게 하기 위한 템플릿 클래스로 사용하시면 됩니다.
 * 기본 설정 데미지는 대상 최대 체력의 50%입니다. (10% x 5번)
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGE_GGFTickDamageWithHealthRatio : public UGameplayEffect
{
    GENERATED_BODY()

public:
    UGE_GGFTickDamageWithHealthRatio();
};
