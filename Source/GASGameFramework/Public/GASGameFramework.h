// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGASGameFrameworkModule : public IModuleInterface
{
public:
	/* IModuleInterface implementation */

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
    // GAS를 위한 설정
    void InitializeForGameplayAbilitySystem();

    // 설정 파일 리로드
    void ReloadConfigs();
};
