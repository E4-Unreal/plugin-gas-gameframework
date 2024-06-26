// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GGFPlayerAbilitySystem.h"
#include "GGFPlayerCharacterAbilitySystem.generated.h"

/**
 * GASGameFramework에서 작성된 기본 어빌리티가 설정되어있는 플레이어 전용 ASC
 */
UCLASS()
class GGFCHARACTERSYSTEM_API UGGFPlayerCharacterAbilitySystem : public UGGFPlayerAbilitySystem
{
    GENERATED_BODY()

public:
    UGGFPlayerCharacterAbilitySystem();
};
