// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGASGameFrameworkModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
    // GAS를 위한 설정
    void InitializeForGameplayAbilitySystem();

    // 설정 파일 리로드
    void ReloadConfigs();

#if WITH_EDITOR
    // 디테일 패널에 커스텀 섹션 추가
    void RegisterSectionMappings();
#endif
};
