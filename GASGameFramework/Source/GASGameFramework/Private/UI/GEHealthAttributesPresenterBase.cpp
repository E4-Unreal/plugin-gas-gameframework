// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGFHealthAttributesPresenterBase.h"

#include "AbilitySystemComponent.h"
#include "Attributes/GGFHealthAttributes.h"

DEFINE_ATTRIBUTE_VALUE_CHANGGF_HANDLE(UGGFHealthAttributesPresenterBase, Health)
DEFINE_ATTRIBUTE_VALUE_CHANGGF_HANDLE(UGGFHealthAttributesPresenterBase, MaxHealth)
DEFINE_ATTRIBUTE_VALUE_CHANGGF_HANDLE(UGGFHealthAttributesPresenterBase, HealthRegenRate)

void UGGFHealthAttributesPresenterBase::GetAttributeValues()
{
    Super::GetAttributeValues();

    UPDATE_ATTRIBUTE_VALUE(UGGFHealthAttributes, Health)
    UPDATE_ATTRIBUTE_VALUE(UGGFHealthAttributes, MaxHealth)
    UPDATE_ATTRIBUTE_VALUE(UGGFHealthAttributes, HealthRegenRate)
}

void UGGFHealthAttributesPresenterBase::BindAttributeValueChangeEvents()
{
    Super::BindAttributeValueChangeEvents();

    BIND_ATTRIBUTE_VALUE_CHANGGF_DELEGATE(UGGFHealthAttributes, Health)
    BIND_ATTRIBUTE_VALUE_CHANGGF_DELEGATE(UGGFHealthAttributes, MaxHealth)
    BIND_ATTRIBUTE_VALUE_CHANGGF_DELEGATE(UGGFHealthAttributes, HealthRegenRate)
}

void UGGFHealthAttributesPresenterBase::UnBindAttributeValueChangeEvents()
{
    Super::UnBindAttributeValueChangeEvents();

    UNBIND_ATTRIBUTE_VALUE_CHANGGF_DELEGATE(UGGFHealthAttributes, Health)
    UNBIND_ATTRIBUTE_VALUE_CHANGGF_DELEGATE(UGGFHealthAttributes, MaxHealth)
    UNBIND_ATTRIBUTE_VALUE_CHANGGF_DELEGATE(UGGFHealthAttributes, HealthRegenRate)
}
