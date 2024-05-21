// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableActorWithUI.h"

#include "Blueprint/UserWidget.h"

bool AGGFInteractableActorWithUI::StartInteraction_Implementation(AActor* OtherActor)
{
    // 상위 클래스에서 문제가 발생한 경우 무시
    if(!Super::StartInteraction_Implementation(OtherActor)) return false;

    // 폰 검사
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if(!OtherPawn) return false;

    // 로컬 플레이어 검사
    if(OtherPawn->IsPlayerControlled() && OtherPawn->IsLocallyControlled())
    {
        // 플레이어 컨트롤러 캐스팅
        APlayerController* LocalPlayerController = CastChecked<APlayerController>(OtherPawn->Controller);

        // 위젯 생성
        CreateLocalPlayerWidget(LocalPlayerController);

        if(Widget)
        {
            // 위젯 표시
            Widget->AddToViewport();
        }

        return true;
    }

    return false;
}

bool AGGFInteractableActorWithUI::Deactivate_Implementation(AActor* OtherActor)
{
    // 상위 클래스에서 문제가 발생한 경우
    if(!Super::Deactivate_Implementation(OtherActor)) return false;

    // 폰 검사
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if(!OtherPawn) return false;

    // 로컬 플레이어 검사
    if(OtherPawn->IsPlayerControlled() && OtherPawn->IsLocallyControlled())
    {
        // 플레이어 컨트롤러 캐스팅
        APlayerController* LocalPlayerController = CastChecked<APlayerController>(OtherPawn->Controller);

        if(Widget)
        {
            // 위젯 숨기기
            Widget->RemoveFromParent();
        }

        return true;
    }

    return false;
}

void AGGFInteractableActorWithUI::CreateLocalPlayerWidget(APlayerController* PlayerController)
{
    // 로컬 플레이어 컨트롤러 검사
    if(PlayerController == nullptr || !PlayerController->IsLocalController()) return;

    // 유효성 검사
    if(!WidgetClass) return;

    // 이미 생성되어 있는 경우
    if(Widget) return;

    // 위젯 생성
    Widget = CreateWidget(PlayerController, WidgetClass);
}
