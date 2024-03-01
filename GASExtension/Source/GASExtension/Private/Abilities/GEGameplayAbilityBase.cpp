// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GEGameplayAbilityBase.h"

#include "AttributeSets/GEHealthAttributeSet.h"

UGEGameplayAbilityBase::UGEGameplayAbilityBase()
{
    // 기본 인스턴싱 정책 설정
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // 기본 Blocking 태그 설정
    ActivationBlockedTags.AddTag(GEGameplayTags::DeadTag);
}
