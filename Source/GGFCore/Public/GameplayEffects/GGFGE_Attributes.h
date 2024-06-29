// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffects/GGFGameplayEffect.h"
#include "GGFGE_Attributes.generated.h"

/**
 * 어트리뷰트 전용 게임플레이 이펙트 클래스입니다.
 */
UCLASS()
class GGFCORE_API UGGFGE_Attributes : public UGGFGameplayEffect
{
    GENERATED_BODY()

protected:
    DEFINE_ATTRIBUTE_MODIFIER_PTR(Health);
    DEFINE_ATTRIBUTE_MODIFIER_PTR(Mana);
    DEFINE_ATTRIBUTE_MODIFIER_PTR(Shield);
    DEFINE_ATTRIBUTE_MODIFIER_PTR(Stamina);

public:
    UGGFGE_Attributes();
};
