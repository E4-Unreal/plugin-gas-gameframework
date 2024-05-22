// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableMenuActor.h"

#include "Blueprint/UserWidget.h"

AGGFInteractableMenuActor::AGGFInteractableMenuActor()
{
    /* 블루프린트 에셋 기본 할당 */
    static ConstructorHelpers::FClassFinder<UUserWidget> InteractionMenuWidgetClassFinder(TEXT("/GASGameFramework/InteractionSystem/WBP_InteractionMenu_Sample.WBP_InteractionMenu_Sample_C"));
    if (InteractionMenuWidgetClassFinder.Succeeded())
    {
        MenuWidgetClass = InteractionMenuWidgetClassFinder.Class;
    }
}

void AGGFInteractableMenuActor::OnLocalPlayerPawnStartInteraction_Implementation(APawn* LocalPlayerPawn)
{
    Super::OnLocalPlayerPawnStartInteraction_Implementation(LocalPlayerPawn);

    // 위젯 생성
    CreateLocalPlayerWidget(LocalPlayerPawn);
\
    // 위젯 표시
    if(MenuWidget) MenuWidget->AddToViewport();
}

void AGGFInteractableMenuActor::OnLocalPlayerPawnDeactivate_Implementation(APawn* LocalPlayerPawn)
{
    Super::OnLocalPlayerPawnDeactivate_Implementation(LocalPlayerPawn);

    // 위젯 숨기기
    if(MenuWidget) MenuWidget->RemoveFromParent();
}

void AGGFInteractableMenuActor::CreateLocalPlayerWidget(APawn* LocalPlayer)
{
    // 유효성 검사
    if(!MenuWidgetClass) return;

    // 이미 생성되어 있는 경우
    if(MenuWidget) return;

    // 위젯 생성
    MenuWidget = CreateWidget(CastChecked<APlayerController>(LocalPlayer->Controller), MenuWidgetClass);
}
