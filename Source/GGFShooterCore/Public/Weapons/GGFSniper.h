// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFProjectileFireArm.h"
#include "GGFSniper.generated.h"

// TODO 리팩토링
/**
 * 조준 시 스코프 UI 표시 기능이 추가된 저격총 전용 총기 클래스입니다.
 */
UCLASS()
class GGFSHOOTERCORE_API AGGFSniper : public AGGFProjectileFireArm
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> ScopeWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UUserWidget> ScopeWidget;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void ShowScopeWidget(bool bShow);
};
