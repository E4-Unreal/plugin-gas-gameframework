// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GGFCrosshairWidget.generated.h"

class UImage;

/**
 * 크로스헤어 전용 위젯 클래스
 */
UCLASS()
class GGFSHOOTERCORE_API UGGFCrosshairWidget : public UUserWidget
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(BlueprintGetter = GetCenterCrosshairImage, meta = (BindWidget))
    TObjectPtr<UImage> CenterCrosshairImage;

    UPROPERTY(BlueprintGetter = GetTopCrosshairImage, meta = (BindWidget))
    TObjectPtr<UImage> TopCrosshairImage;

    UPROPERTY(BlueprintGetter = GetBottomCrosshairImage, meta = (BindWidget))
    TObjectPtr<UImage> BottomCrosshairImage;

    UPROPERTY(BlueprintGetter = GetRightCrosshairImage, meta = (BindWidget))
    TObjectPtr<UImage> RightCrosshairImage;

    UPROPERTY(BlueprintGetter = GetLeftCrosshairImage, meta = (BindWidget))
    TObjectPtr<UImage> LeftCrosshairImage;

public:
    /* UserWidget */

    virtual void NativePreConstruct() override;

protected:
    /* 메서드 */

    // 할당된 텍스처가 없는 경우 알파를 0으로 설정합니다.
    UFUNCTION(BlueprintCallable)
    virtual void RefreshImage(UImage* TargetImage);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UImage* GetCenterCrosshairImage() const { return CenterCrosshairImage; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UImage* GetTopCrosshairImage() const { return TopCrosshairImage; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UImage* GetBottomCrosshairImage() const { return BottomCrosshairImage; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UImage* GetRightCrosshairImage() const { return RightCrosshairImage; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UImage* GetLeftCrosshairImage() const { return LeftCrosshairImage; }
};
