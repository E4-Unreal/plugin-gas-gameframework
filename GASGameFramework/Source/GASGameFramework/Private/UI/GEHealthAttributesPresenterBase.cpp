// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GEHealthAttributesPresenterBase.h"

#include "AbilitySystemComponent.h"
#include "Attributes/GEHealthAttributes.h"

DEFINE_ATTRIBUTE_VALUE_CHANGE_HANDLE(UGEHealthAttributesPresenterBase, Health)
DEFINE_ATTRIBUTE_VALUE_CHANGE_HANDLE(UGEHealthAttributesPresenterBase, MaxHealth)
DEFINE_ATTRIBUTE_VALUE_CHANGE_HANDLE(UGEHealthAttributesPresenterBase, HealthRegenRate)

void UGEHealthAttributesPresenterBase::GetAttributeValues()
{
    Super::GetAttributeValues();

    UPDATE_ATTRIBUTE_VALUE(UGEHealthAttributes, Health)
    UPDATE_ATTRIBUTE_VALUE(UGEHealthAttributes, MaxHealth)
    UPDATE_ATTRIBUTE_VALUE(UGEHealthAttributes, HealthRegenRate)
}

void UGEHealthAttributesPresenterBase::BindAttributeValueChangeEvents()
{
    Super::BindAttributeValueChangeEvents();

    BIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, Health)
    BIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, MaxHealth)
    BIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, HealthRegenRate)
}

void UGEHealthAttributesPresenterBase::UnBindAttributeValueChangeEvents()
{
    Super::UnBindAttributeValueChangeEvents();

    UNBIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, Health)
    UNBIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, MaxHealth)
    UNBIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(UGEHealthAttributes, HealthRegenRate)
}
