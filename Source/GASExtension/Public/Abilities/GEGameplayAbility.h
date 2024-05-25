// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GEGameplayAbility.generated.h"

/**
 * 자주 사용하는 정책과 게임플레이 태그 설정이 적용된 게임플레이 어빌리티 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API UGEGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UGEGameplayAbility();
};
