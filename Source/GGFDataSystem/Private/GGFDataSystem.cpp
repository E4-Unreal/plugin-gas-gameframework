#include "GGFDataSystem.h"

#include "GGFDataSystemSetting.h"
#include "Developer/Settings/Public/ISettingsModule.h"

IMPLEMENT_MODULE(FGGFDataSystemModule, GGFDataSystem)

#define LOCTEXT_NAMESPACE "FGGFDataSystemModule"

void FGGFDataSystemModule::StartupModule()
{
    if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->RegisterSettings("Project", "Plugins", "GGFDataSystem",
            LOCTEXT("RuntimeSettingsName", "GGF DataSystem"), LOCTEXT("RuntimeSettingsDescription", "GGF DataSystem"),
            GetMutableDefault<UGGFDataSystemSetting>());
    }
}

void FGGFDataSystemModule::ShutdownModule()
{
    if(ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "GGFDataSystem");
    }
}

#undef LOCTEXT_NAMESPACE
