// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GGFHitEffect.generated.h"

/**
 * HitEffect Definition에서 사용할 컴포넌트 클래스입니다.
 * 어떤 피격 효과를 어떻게 스폰할지 정의합니다.
 */
UCLASS(Abstract, Const, DefaultToInstanced, EditInlineNew, CollapseCategories, Within=GGFHitEffectDefinition)
class GASGAMEFRAMEWORK_API UGGFHitEffect : public UObject
{
    GENERATED_BODY()

public:
    virtual void SpawnHitEffect(const FHitResult& HitResult) const { };
};
