#include "GGFItemSystem.h"

#include "GGFItemSystemSetting.h"
#include "Developer/Settings/Public/ISettingsModule.h"

IMPLEMENT_MODULE(FGGFItemSystemModule, GGFItemSystem)

#define LOCTEXT_NAMESPACE "FGGFItemSystemModule"

void FGGFItemSystemModule::StartupModule()
{
    if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->RegisterSettings("Project", "Plugins", "GGFItemSystem",
            LOCTEXT("RuntimeSettingsName", "GGF ItemSystem"), LOCTEXT("RuntimeSettingsDescription", "GGF ItemSystem"),
            GetMutableDefault<UGGFItemSystemSetting>());
    }
}

void FGGFItemSystemModule::ShutdownModule()
{
    if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "GGFItemSystem");
    }
}

#undef LOCTEXT_NAMESPACE
