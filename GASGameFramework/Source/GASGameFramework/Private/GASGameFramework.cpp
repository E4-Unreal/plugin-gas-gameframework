// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASGameFramework.h"

#include "AbilitySystemGlobals.h"
#include "PropertyEditorModule.h"

IMPLEMENT_MODULE(FGASGameFrameworkModule, GASGameFramework)

#define LOCTEXT_NAMESPACE "FGASGameFrameworkModule"

void FGASGameFrameworkModule::StartupModule()
{
    // TargetData를 사용하기 위한 초기화
    UAbilitySystemGlobals::Get().InitGlobalData();

    /* 디테일 패널에 커스텀 섹션 추가 */
#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "Custom Detail"
    static const FName PropertyEditor("PropertyEditor");
    FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);

    // Actor 클래스에 커스텀 섹션 생성 및 카테고리 추가
    const TSharedRef<FPropertySection> ActorConfigSection = PropertyModule.FindOrCreateSection("Actor", "Config", LOCTEXT("Config", "설정"));
    ActorConfigSection->AddCategory("Config");
    ActorConfigSection->AddCategory("State");

    // ActorComponent 클래스에 커스텀 섹션 생성 및 카테고리 추가
    const TSharedRef<FPropertySection> ActorComponentConfigSection = PropertyModule.FindOrCreateSection("ActorComponent", "Config", LOCTEXT("Config", "설정"));
    ActorComponentConfigSection->AddCategory("Config");
    ActorComponentConfigSection->AddCategory("State");

#undef LOCTEXT_NAMESPACE
#endif
}

void FGASGameFrameworkModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
