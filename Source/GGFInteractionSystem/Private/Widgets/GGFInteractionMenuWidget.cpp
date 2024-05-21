// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GGFInteractionMenuWidget.h"

#include "EnhancedInputComponent.h"

void UGGFInteractionMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 폰에 대한 플레이어 입력 비활성화
    DisablePlayerInputForPawn();

    // 입력 바인딩
    BindEnhancedInputAction(CastChecked<UEnhancedInputComponent>(GetOwningPlayer()->InputComponent));
}

void UGGFInteractionMenuWidget::NativeDestruct()
{
    Super::NativeDestruct();

    // 입력 언바인딩
    UnBindEnhancedInputAction(CastChecked<UEnhancedInputComponent>(GetOwningPlayer()->InputComponent));

    // 폰에 대한 플레이어 입력 활성화
    EnablePlayerInputForPawn();
}

void UGGFInteractionMenuWidget::EnablePlayerInputForPawn()
{
    /* 컨트롤러 설정 */
    APlayerController* LocalPlayerController = GetOwningPlayer();

    // 마우스 커서 숨기기 및 이벤트 비활성화
    LocalPlayerController->bShowMouseCursor = false;
    LocalPlayerController->bEnableClickEvents = false;
    LocalPlayerController->bEnableMouseOverEvents = false;

    /* 폰 설정 */
    APawn* LocalPlayerPawn = LocalPlayerController->GetPawn();
    LocalPlayerPawn->EnableInput(LocalPlayerController);
}

void UGGFInteractionMenuWidget::DisablePlayerInputForPawn()
{
    /* 컨트롤러 설정 */
    APlayerController* LocalPlayerController = GetOwningPlayer();

    // 마우스 커서 위치 초기화
    int32 ViewportSizeX;
    int32 ViewportSizeY;
    LocalPlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
    LocalPlayerController->SetMouseLocation(ViewportSizeX / 2, ViewportSizeY / 2);

    // 마우스 커서 표시 및 이벤트 활성화
    LocalPlayerController->bShowMouseCursor = true;
    LocalPlayerController->bEnableClickEvents = true;
    LocalPlayerController->bEnableMouseOverEvents = true;

    /* 폰 설정 */
    APawn* LocalPlayerPawn = LocalPlayerController->GetPawn();
    LocalPlayerPawn->DisableInput(LocalPlayerController);
}

void UGGFInteractionMenuWidget::BindEnhancedInputAction(UEnhancedInputComponent* EnhancedInputComponent)
{
    // 취소 입력 바인딩
    CancelBindingHandle = EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Triggered, this, &ThisClass::RemoveFromParent).GetHandle();
}

void UGGFInteractionMenuWidget::UnBindEnhancedInputAction(UEnhancedInputComponent* EnhancedInputComponent)
{
    // 취소 입력 언바인딩
    EnhancedInputComponent->RemoveBindingByHandle(CancelBindingHandle);
}
