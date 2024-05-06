// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGFHealthAttributesPresenterBase.h"

#include "AbilitySystemComponent.h"
#include "Attributes/GEHealthAttributes.h"

DEFINE_ATTRIBUTE_VALUE_CHANGE_HANDLE(UGGFHealthAttributesPresenterBase, Health)
DEFINE_ATTRIBUTE_VALUE_CHANGE_HANDLE(UGGFHealthAttributesPresenterBase, MaxHealth)
DEFINE_ATTRIBUTE_VALUE_CHANGE_HANDLE(UGGFHealthAttributesPresenterBase, HealthRegenRate)

void UGGFHealthAttributesPresenterBase::GetAttributeValues()
{
    Super::GetAttributeValues();

    UPDATE_ATTRIBUTE_VALUE(UGEHealthAttributes, Health)
    UPDATE_ATTRIBUTE_VALUE(UGEHealthAttributes, MaxHealth)
    UPDATE_ATTRIBUTE_VALUE(UGEHealthAttributes, HealthRegenRate)
}

void UGGFHealthAttributesPresenterBase::BindAttributeValueChangeEvents()
{
    Super::BindAttributeValueChangeEvents();

    BIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, Health)
    BIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, MaxHealth)
    BIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, HealthRegenRate)
}

void UGGFHealthAttributesPresenterBase::UnBindAttributeValueChangeEvents()
{
    Super::UnBindAttributeValueChangeEvents();

    UNBIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, Health)
    UNBIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, MaxHealth)
    UNBIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, HealthRegenRate)
}
