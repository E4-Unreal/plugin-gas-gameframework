// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GEAttributesPresenterBase.h"
#include "GEHealthAttributesPresenterBase.generated.h"

/**
 * GEAttributesPresenterBase 클래스를 상속받아 GEHealthAttributes를 UI에 바인딩하기 위한 사용 예시입니다.
 * 이 클래스를 직접 상속받아 사용하는 것 역시 가능합니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGEHealthAttributesPresenterBase : public UGEAttributesPresenterBase
{
    GENERATED_BODY()

    DECLARE_ATTRIBUTE_VALUE_CHANGE_HANDLE(Health)
    DECLARE_ATTRIBUTE_VALUE_CHANGE_HANDLE(MaxHealth)
    DECLARE_ATTRIBUTE_VALUE_CHANGE_HANDLE(HealthRegenRate)

protected:
    DECLARE_ATTRIBUTE_SETTER(Health)
    DECLARE_ATTRIBUTE_SETTER(MaxHealth)
    DECLARE_ATTRIBUTE_SETTER(HealthRegenRate)

    /* GEAttributesPresenter */

    virtual void GetAttributeValues() override;
    virtual void BindAttributeValueChangeEvents() override;
    virtual void UnBindAttributeValueChangeEvents() override;
};
