// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GGFPickupWidget.generated.h"

class AGGFPickup;
class UTextBlock;
class UGGFItemDefinition;

/**
 * Pickup 전용 위젯 클래스
 */
UCLASS()
class GGFITEMSYSTEM_API UGGFPickupWidget : public UUserWidget
{
    GENERATED_BODY()

    TWeakObjectPtr<AGGFPickup> Pickup;

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DisplayNameText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> AmountText;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetPickup(AGGFPickup* Target);

protected:
    UFUNCTION(BlueprintCallable)
    virtual void Update();
};
