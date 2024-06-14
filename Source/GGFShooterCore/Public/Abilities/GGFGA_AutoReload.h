// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFGA_Reload.h"
#include "GGFGA_AutoReload.generated.h"

/**
 * 재장전이 필요한 상황에서 Fire 입력 시 설정에 따라 자동 재장전을 진행합니다.
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFGA_AutoReload : public UGGFGA_Reload
{
    GENERATED_BODY()

public:
    UGGFGA_AutoReload();

protected:
    /* GEGameplayAbility */

    virtual bool InternalCanActivate() override;
};
