// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/GGFGA_AutoReload.h"

#include "GGFShooterGameplayTags.h"

UGGFGA_AutoReload::UGGFGA_AutoReload()
{
    // 입력 태그 설정
    InputTag = Input::Fire;
}

bool UGGFGA_AutoReload::InternalCanActivate()
{
    return Super::InternalCanActivate() && GetFireArm()->IsOutOfAmmo();
}
