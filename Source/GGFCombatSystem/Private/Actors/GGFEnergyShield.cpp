// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFEnergyShield.h"

#include "AbilitySystem/GGFDamageableAbilitySystem.h"

AGGFEnergyShield::AGGFEnergyShield(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DisplayMesh */
    GetDisplayMesh()->SetCollisionProfileName("IgnoreOnlyPawn");

    /* DamageableAbilitySystem */
    if(auto CastedAbilitySystem = Cast<UGGFDamageableAbilitySystem>(GetAbilitySystem()))
    {
        CastedAbilitySystem->MaxHealth = 500;
    }

    /* 기본 에셋 설정 */
    ConstructorHelpers::FObjectFinder<UStaticMesh> DisplayMeshFinder(TEXT("/E4Effects/Meshes/SM_EnergyShield_Sphere"));
    if(DisplayMeshFinder.Succeeded()) GetDisplayMesh()->SetStaticMesh(DisplayMeshFinder.Object);
}
