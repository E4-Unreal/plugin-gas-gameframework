// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/GGFPickupWidget.h"

#include "Components/TextBlock.h"
#include "Pickup/GGFPickup.h"

void UGGFPickupWidget::SetPickup(AGGFPickup* Target)
{
    if(Target == nullptr) return;
    Pickup = Target;

    // UI 갱신 이벤트 바인딩
    Pickup->OnUpdated.AddDynamic(this, &ThisClass::Update);

    // UI 갱신
    Update();
}

void UGGFPickupWidget::Update()
{
    if(Pickup.IsValid())
    {
        // DisplayName
        DisplayNameText->SetText(Pickup->GetDisplayNameText());

        // Amount
        int32 NewAmount = Pickup->GetAmount();
        AmountText->SetText(NewAmount == 1 ? FText::GetEmpty() : FText::FromString("(" + FString::FromInt(NewAmount) + ")"));
    }
}
