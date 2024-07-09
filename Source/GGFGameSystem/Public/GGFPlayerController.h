// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/GGFTeamInterface.h"
#include "GGFPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * GASGameFramework 플러그인 전용 플레이어 컨트롤러
 */
UCLASS()
class GGFGAMESYSTEM_API AGGFPlayerController : public APlayerController, public IGGFTeamInterface
{
    GENERATED_BODY()

protected:
    // 플레이어 전용 입력 매핑 컨텍스트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Input")
    TObjectPtr<UInputMappingContext> MappingContext;

    // 이전 플레이어 관전을 위한 입력 액션
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Input")
    TObjectPtr<UInputAction> SpectatePreviousAction;

    // 다음 플레이어 관전을 위한 입력 액션
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Input")
    TObjectPtr<UInputAction> SpectateNextAction;

    // 플레이어 메뉴을 열고 닫기 위한 입력 액션
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Input")
    TObjectPtr<UInputAction> MenuAction;

    // 플레이어 메뉴 위젯 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    // 플레이어 HUD 위젯 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|UI")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    // 메뉴 위젯 인스턴스
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|UI", Transient)
    TObjectPtr<UUserWidget> MenuWidget;

    // 플레이어 HUD 위젯 인스턴스
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetHUDWidget, Category = "State|UI", Transient)
    TObjectPtr<UUserWidget> HUDWidget;

public:
    AGGFPlayerController();

    /* Actor */

    virtual void BeginPlay() override;

    /* GGFTeamInterface */

    virtual uint8 GetTeamID_Implementation() const override;
    virtual void SetTeamID_Implementation(uint8 NewTeamID) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UUserWidget* GetHUDWidget() const { return HUDWidget; }

protected:
    /* 이벤트 */

    // 이전 플레이어 관전 입력 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnSpectatePreviousActionTriggered();

    // 다음 플레이어 관전 입력 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnSpectateNextActionTriggered();

    // 메뉴 입력 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void OnMenuActionTriggered();

    /* 메서드 */

    // 플레이어 HUD 위젯 생성
    UFUNCTION(BlueprintCallable)
    virtual void CreateHUDWidget();

    /* RPC */

    // 이전 플레이어 관전 (서버)
    UFUNCTION(Server, Reliable)
    void ServerSpectatePrevious();

    // 다음 플레이어 관전 (서버)
    UFUNCTION(Server, Reliable)
    void ServerSpectateNext();
};
