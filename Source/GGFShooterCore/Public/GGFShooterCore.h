#pragma once

#include "CoreMinimal.h"

class FGGFShooterCoreModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
