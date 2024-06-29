// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFUserWidget.h"
#include "GGFMenuWidget.generated.h"

// TODO 향상된 입력 액션으로 대체, CommonWidget
/**
 * 메뉴 전용 위젯 클래스로 게임 입력이 비활성화되며 마우스 커서가 표시됩니다.
 */
UCLASS()
class GGFWIDGETSYSTEM_API UGGFMenuWidget : public UGGFUserWidget
{
    GENERATED_BODY()

public:
    UGGFMenuWidget(const FObjectInitializer& ObjectInitializer);

protected:
    /* UserWidget */

    // AddToViewPort
    virtual void NativeConstruct() override;

    // RemoveFromParent
    virtual void NativeDestruct() override;

    // TODO 향상된 입력 시스템 대체?
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

    /* 메서드 */
    // 폰에 대한 플레이어 입력 활성화
    virtual void EnablePlayerInputForPawn();

    // 폰에 대한 플레이어 입력 비활성화
    virtual void DisablePlayerInputForPawn();
};
