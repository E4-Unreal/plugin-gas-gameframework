﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GEWeaponAbilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class GASEXTENSION_API UGEWeaponAbilityInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 무기 전용 어빌리티 인스턴스에서 무기 레퍼런스를 주입하기 위한 인터페이스
 */
class GASEXTENSION_API IGEWeaponAbilityInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetWeapon(AActor* InWeapon);
};
