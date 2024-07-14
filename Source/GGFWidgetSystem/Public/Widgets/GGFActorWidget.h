// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GGFActorWidget.generated.h"

/**
 *
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFActorWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    TWeakObjectPtr<AActor> Actor;

public:
    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetActor(AActor* NewActor);

protected:
    /* 메서드 */

    // Actor 현재 정보 반영
    virtual void Fetch();

    // 새로운 Actor 이벤트 바인딩
    virtual void BindActorEvents(AActor* NewActor);

    // 기존 Actor 이벤트 언바인딩
    virtual void UnbindActorEvents(AActor* OldActor);

    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE AActor* GetActor() const { return Actor.Get(); }
};
