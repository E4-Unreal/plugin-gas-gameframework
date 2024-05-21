// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "GGFInteractionMenuWidget.generated.h"

class UInputAction;

// TODO UI 화면을 클릭한 후 Cancel 입력을 하면 마우스 회전의 경우 마우스 입력을 해야 정상적으로 복원되는 버그가 있습니다.
/**
 * 상호작용 오브젝트의 상호작용 시 로컬 플레이어에게 표시할 위젯 클래스입니다.
 */
UCLASS()
class GGFINTERACTIONSYSTEM_API UGGFInteractionMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    // UI 종료를 위한 입력 액션으로 주로 ESC 키를 사용합니다.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    TObjectPtr<UInputAction> CancelAction;

    uint32 CancelBindingHandle;

protected:
    /* UserWidget */

    // AddToViewPort
    virtual void NativeConstruct() override;

    // RemoveFromParent
    virtual void NativeDestruct() override;

    /* 메서드 */
    // 폰에 대한 플레이어 입력 활성화
    virtual void EnablePlayerInputForPawn();

    // 폰에 대한 플레이어 입력 비활성화
    virtual void DisablePlayerInputForPawn();

    // UI 입력 액션 바인딩
    virtual void BindEnhancedInputAction(UEnhancedInputComponent* EnhancedInputComponent);

    // UI 입력 액션 언바인딩
    virtual void UnBindEnhancedInputAction(UEnhancedInputComponent* EnhancedInputComponent);
};
