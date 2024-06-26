#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGGFCoreModule : public IModuleInterface
{
public:
    /* ModuleInterface */

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    // GAS를 위한 설정
    void InitializeForGameplayAbilitySystem();

#if WITH_EDITOR
    // 디테일 패널에 커스텀 섹션 추가
    void RegisterSectionMappings();
#endif
};
