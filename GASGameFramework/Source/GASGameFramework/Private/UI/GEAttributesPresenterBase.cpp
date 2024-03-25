// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGFAttributesPresenterBase.h"

void UGGFAttributesPresenterBase::SetAbilitySystem(UAbilitySystemComponent* InAbilitySystem)
{
    // 기존 AbilitySystem 등록 해제
    if(AbilitySystem)
    {
        UnBindAttributeValueChangeEvents();
    }

    // 새로운 AbilitySystem 등록
    AbilitySystem = InAbilitySystem;

    if(AbilitySystem)
    {
        GetAttributeValues();
        BindAttributeValueChangeEvents();
        AddToViewport();
    }
    else
    {
        RemoveFromParent();
    }
}

void UGGFAttributesPresenterBase::GetAttributeValues()
{
}

void UGGFAttributesPresenterBase::BindAttributeValueChangeEvents()
{
}

void UGGFAttributesPresenterBase::UnBindAttributeValueChangeEvents()
{
}
