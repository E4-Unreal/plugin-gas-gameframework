// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GGFInteractionMenuWidget.generated.h"

class UInputAction;

// TODO 에디터 상에서 UI 조작 중 캐릭터가 죽으면 다른 클라이언트 플레이어의 입력이 먹통이 되는 버그가 발견되었습니다. 빌드 테스트는 아직입니다.
/**
 * 상호작용 오브젝트의 상호작용 시 로컬 플레이어에게 표시할 위젯 클래스입니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFInteractionMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UGGFInteractionMenuWidget(const FObjectInitializer& ObjectInitializer);

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
