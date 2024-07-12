// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GGFPlayerWidget.generated.h"

class UGGFActorWidget;

/**
 * HUD에 표시할 플레이어 전용 위젯으로 대상 PlayerState를 레퍼런스로 가지고 있습니다.
 * 주로 다른 플레이어 정보를 표시하기 위해 사용됩니다.
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFPlayerWidget : public UUserWidget
{
    GENERATED_BODY()

    TWeakObjectPtr<APlayerState> PlayerState;

    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr<UGGFActorWidget> PlayerPawnWidget;

public:
    UFUNCTION(BlueprintCallable)
    virtual void SetPlayerState(APlayerState* NewPlayerState);

protected:
    /* 이벤트 */

    UFUNCTION()
    virtual void OnPlayerStatePawnSet(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);

    /* 메서드 */

    virtual void UpdatePlayerPawnWidget();

    virtual void BindPlayerStateEvents(APlayerState* NewPlayerState);
    virtual void UnbindPlayerStateEvents(APlayerState* OldPlayerState);

    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE APlayerState* GetPlayerState() const { return PlayerState.Get(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UGGFActorWidget* GetPlayerPawnWidget() const { return PlayerPawnWidget; }
};
