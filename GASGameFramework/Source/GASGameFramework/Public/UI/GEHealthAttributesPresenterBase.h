// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GGFAttributesPresenterBase.h"
#include "GGFHealthAttributesPresenterBase.generated.h"

/**
 * GGFAttributesPresenterBase 클래스를 상속받아 GGFHealthAttributes를 UI에 바인딩하기 위한 사용 예시입니다.
 * 이 클래스를 직접 상속받아 사용하는 것 역시 가능합니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFHealthAttributesPresenterBase : public UGGFAttributesPresenterBase
{
    GENERATED_BODY()

    DECLARE_ATTRIBUTE_VALUE_CHANGGF_HANDLE(Health)
    DECLARE_ATTRIBUTE_VALUE_CHANGGF_HANDLE(MaxHealth)
    DECLARE_ATTRIBUTE_VALUE_CHANGGF_HANDLE(HealthRegenRate)

protected:
    DECLARE_ATTRIBUTE_SETTER(Health)
    DECLARE_ATTRIBUTE_SETTER(MaxHealth)
    DECLARE_ATTRIBUTE_SETTER(HealthRegenRate)

    /* GGFAttributesPresenter */

    virtual void GetAttributeValues() override;
    virtual void BindAttributeValueChangeEvents() override;
    virtual void UnBindAttributeValueChangeEvents() override;
};
