// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/GGFInteractableMenuActor.h"

#include "Blueprint/UserWidget.h"

AGGFInteractableMenuActor::AGGFInteractableMenuActor()
{
    /* 초기화 */
    DisplayName = "Interactable Menu Object";
    InteractionInfo = "Show Menu";

    /* 블루프린트 에셋 기본 할당 */
    // LevelPrototyping 플러그인
    GetDisplayMesh()->SetRelativeLocation(FVector(0, 0, 100));
    GetDisplayMesh()->SetRelativeScale3D(FVector(1, 0.1, 2));

    // GASGameFramework 플러그인
    static ConstructorHelpers::FClassFinder<UUserWidget> InteractionMenuWidgetClassFinder(TEXT("/GASGameFramework/Objects/Interactable/WBP_InteractionMenu_Sample.WBP_InteractionMenu_Sample_C"));
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
