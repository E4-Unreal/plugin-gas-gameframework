// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFInteractionMenuWidget.h"

UGGFInteractionMenuWidget::UGGFInteractionMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    SetIsFocusable(true);
}

void UGGFInteractionMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 폰에 대한 플레이어 입력 비활성화
    DisablePlayerInputForPawn();
}

void UGGFInteractionMenuWidget::NativeDestruct()
{
    // 폰에 대한 플레이어 입력 활성화
    EnablePlayerInputForPawn();

    Super::NativeDestruct();
}

FReply UGGFInteractionMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    // ESC 입력 시 위젯 닫기
    if(InKeyEvent.GetKeyCode() == 27) RemoveFromParent();

    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UGGFInteractionMenuWidget::EnablePlayerInputForPawn()
{
    /* 컨트롤러 설정 */
    APlayerController* LocalPlayerController = GetOwningPlayer();
    if(!LocalPlayerController) return;

    // 마우스 커서 숨기기
    LocalPlayerController->bShowMouseCursor = false;
    LocalPlayerController->SetInputMode(FInputModeGameOnly());
}

void UGGFInteractionMenuWidget::DisablePlayerInputForPawn()
{
    /* 컨트롤러 설정 */
    APlayerController* LocalPlayerController = GetOwningPlayer();
    if(!LocalPlayerController) return;

    // 포커스 설정
    SetKeyboardFocus();

    // 마우스 커서 위치 초기화
    int32 ViewportSizeX;
    int32 ViewportSizeY;
    LocalPlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
    LocalPlayerController->SetMouseLocation(ViewportSizeX / 2, ViewportSizeY / 2);

    // 마우스 커서 표시
    LocalPlayerController->bShowMouseCursor = true;
    LocalPlayerController->SetInputMode(FInputModeUIOnly());
}
