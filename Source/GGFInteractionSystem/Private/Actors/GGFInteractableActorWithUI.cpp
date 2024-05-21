// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableActorWithUI.h"

#include "Blueprint/UserWidget.h"

void AGGFInteractableActorWithUI::OnLocalPlayerPawnStartInteraction_Implementation(APawn* LocalPlayerPawn)
{
    Super::OnLocalPlayerPawnStartInteraction_Implementation(LocalPlayerPawn);

    // 위젯 생성
    CreateLocalPlayerWidget(LocalPlayerPawn);
\
    // 위젯 표시
    if(Widget) Widget->AddToViewport();
}

void AGGFInteractableActorWithUI::OnLocalPlayerPawnDeactivate_Implementation(APawn* LocalPlayerPawn)
{
    Super::OnLocalPlayerPawnDeactivate_Implementation(LocalPlayerPawn);

    // 위젯 숨기기
    if(Widget) Widget->RemoveFromParent();
}

void AGGFInteractableActorWithUI::CreateLocalPlayerWidget(APawn* LocalPlayer)
{
    // 유효성 검사
    if(!WidgetClass) return;

    // 이미 생성되어 있는 경우
    if(Widget) return;

    // 위젯 생성
    Widget = CreateWidget(CastChecked<APlayerController>(LocalPlayer->Controller), WidgetClass);
}
