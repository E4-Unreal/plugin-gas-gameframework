// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/GGFInputManager.h"

#include "InputMappingContext.h"

UGGFInputManager::UGGFInputManager()
{
    /* GASGameFramework 플러그인 에셋 */
    // Character
    ConstructorHelpers::FObjectFinder<UInputMappingContext> CharacterInputMappingContextFinder(TEXT("/GASGameFramework/Input/Character/IMC_Character.IMC_Character"));
    if(CharacterInputMappingContextFinder.Succeeded()) InputMappingContexts.Emplace(CharacterInputMappingContextFinder.Object);

    ConstructorHelpers::FObjectFinder<UGGFInputConfig> CharacterInputConfigFinder(TEXT("/GASGameFramework/Input/Character/IC_Character.IC_Character"));
    if(CharacterInputConfigFinder.Succeeded()) InputConfigs.Emplace(CharacterInputConfigFinder.Object);

    // Equipment
    ConstructorHelpers::FObjectFinder<UInputMappingContext> EquipmentInputMappingContextFinder(TEXT("/GASGameFramework/Input/Equipment/IMC_Equipment.IMC_Equipment"));
    if(EquipmentInputMappingContextFinder.Succeeded()) InputMappingContexts.Emplace(EquipmentInputMappingContextFinder.Object);

    ConstructorHelpers::FObjectFinder<UGGFInputConfig> EquipmentInputConfigFinder(TEXT("/GASGameFramework/Input/Equipment/IC_Equipment.IC_Equipment"));
    if(EquipmentInputConfigFinder.Succeeded()) InputConfigs.Emplace(EquipmentInputConfigFinder.Object);
}
