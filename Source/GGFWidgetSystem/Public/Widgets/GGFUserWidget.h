// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/GGFWidgetInterface.h"
#include "GGFUserWidget.generated.h"

class UAbilitySystemComponent;

/**
 * GASGameFramework 플러그인에서 범용적으로 사용할 위젯 클래스
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFUserWidget : public UUserWidget, public IGGFWidgetInterface
{
    GENERATED_BODY()

protected:
    // UI에 표시할 정보를 지니고 있는 대상
    TWeakObjectPtr<AActor> TargetActor;

    // TargetActor의 AbilitySystemComponent
    TWeakObjectPtr<UAbilitySystemComponent> TargetSystem;

public:
    /* GGFWidgetInterface */

    virtual void Refresh_Implementation() override;

    /* Getter */

    UFUNCTION(BlueprintPure)
    AActor* GetTargetActor() const { return TargetActor.Get(); }

    UFUNCTION(BlueprintPure)
    UAbilitySystemComponent* GetTargetSystem() const { return TargetSystem.Get(); }

    /* Setter */

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetActor(AActor* NewTargetActor);

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetSystem(UAbilitySystemComponent* NewTargetSystem);
};
