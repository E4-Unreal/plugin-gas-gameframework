// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/GGFTPSAnimInstance.h"
#include "Components/GGFEquipmentManager.h"
#include "GGFEquipment.h"

void UGGFTPSAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    // 유효성 검사
    if(IsNotValid()) return;

    // LeftHand IK
    CalculateLeftHandIK(DeltaSeconds);
}

void UGGFTPSAnimInstance::CalculateLeftHandIK(float DeltaSeconds)
{
    bEnableLeftHandIK = false;
    if(auto EquipmentManager = GetOwningActor()->GetComponentByClass<UGGFEquipmentManager>())
    {
        if(auto SelectedEquipment = Cast<AGGFEquipment>(EquipmentManager->GetSelectedEquipment()))
        {
            if(SelectedEquipment->GetSkeletalMesh()->DoesSocketExist(LeftHandSocketName))
            {
                LeftHandTransform = SelectedEquipment->GetSkeletalMesh()->GetSocketTransform(LeftHandSocketName, RTS_ParentBoneSpace);
                bEnableLeftHandIK = true;
            }
        }
    }
    bEnableLeftHandIK = bEnableLeftHandIK && FMath::IsNearlyZero(GetCurveValue(DisableLeftHandIKCurveName));
}
