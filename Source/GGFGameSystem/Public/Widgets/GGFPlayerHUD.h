// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/GGFTeamTypes.h"
#include "GGFPlayerHUD.generated.h"

class UVerticalBox;
class UGGFPlayerWidget;
struct FGGFTeamInfo;

/**
 * 플레이어 전용 HUD
 */
UCLASS()
class GGFGAMESYSTEM_API UGGFPlayerHUD : public UUserWidget
{
    GENERATED_BODY()

protected:
    /* 컴포넌트 */

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UGGFPlayerWidget> LocalPlayerWidget;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UGGFPlayerWidget> TeamPlayerWidget_1;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UGGFPlayerWidget> TeamPlayerWidget_2;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UGGFPlayerWidget> TeamPlayerWidget_3;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UGGFPlayerWidget>> TeamPlayerWidgets;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FGGFTeamSlot> TeamSlots;

protected:
    /* UserWidget */

    virtual void NativeConstruct() override;

    /* 이벤트 */

    UFUNCTION()
    virtual void OnTeamInfoUpdated(APlayerState* Player, const FGGFTeamInfo& OldTeamInfo, const FGGFTeamInfo& NewTeamInfo);

    /* 메서드 */

    // 팀 플레이어 정보 패치
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void FetchTeamSlots();
};
