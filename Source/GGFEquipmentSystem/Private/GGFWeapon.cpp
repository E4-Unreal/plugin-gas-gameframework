// Fill out your copyright notice in the Description page of Project Settings.

#include "GGFWeapon.h"

#include "Components/GGFWeaponDataManager.h"
#include "Data/GGFWeaponDefinition.h"
#include "Interfaces/GGFCharacterAnimationInterface.h"

AGGFWeapon::AGGFWeapon(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGGFWeaponDataManager>(DataManagerName))
{

}

void AGGFWeapon::Activate_Implementation()
{
    Super::Activate_Implementation();

    // 무기 데이터
    auto WeaponDataManager = CastChecked<UGGFWeaponDataManager>(GetDataManager());
    const auto& Data = WeaponDataManager->GetWeaponData();

    // 캐릭터 애니메이션 클래스 변경
    SetCharacterAnimClass(Data.CharacterAnimClass);

    // 장비 장착 몽타주 재생
    PlayCharacterAnimMontage(Data.EquipMontage, Data.EquipDuration);
}

void AGGFWeapon::Deactivate_Implementation()
{
    Super::Deactivate_Implementation();

    // 무기 데이터
    auto WeaponDataManager = CastChecked<UGGFWeaponDataManager>(GetDataManager());
    const auto& Data = WeaponDataManager->GetWeaponData();

    // 현재 선택된 무기가 없으면 캐릭터에서 자체적으로 기본 애님 클래스로 변경

    // 장비 장착 해제 몽타주 재생
    PlayCharacterAnimMontage(Data.UnequipMontage, Data.UnequipDuration);
}

void AGGFWeapon::OnIDUpdated(int32 NewID)
{
    // 무기 데이터
    auto WeaponDataManager = CastChecked<UGGFWeaponDataManager>(GetDataManager());
    const auto& Data = WeaponDataManager->GetWeaponData();
    GetSkeletalMesh()->SetAnimClass(Data.WeaponAnimClass);

    Super::OnIDUpdated(NewID);
}

void AGGFWeapon::PlayAnimMontage(UAnimMontage* AnimMontage, float Duration) const
{
    // 유효성 검사
    if(AnimMontage == nullptr) return;

    // 무기 애님 몽타주 재생
    if(auto AnimInstance = GetSkeletalMesh()->GetAnimInstance())
    {
        float PlayRate = FMath::IsNearlyZero(Duration) ? 1 : AnimMontage->GetPlayLength() / Duration;
        AnimInstance->Montage_Play(AnimMontage, PlayRate);
    }
}

void AGGFWeapon::SetCharacterAnimClass(TSubclassOf<UAnimInstance> NewAnimClass) const
{
    // 유효성 검사
    if(NewAnimClass == nullptr) return;

    // 캐릭터 애니메이션 클래스 변경
    if(GetOwner()->Implements<UGGFCharacterAnimationInterface>())
    {
        IGGFCharacterAnimationInterface::Execute_SetAnimInstanceClass(GetOwner(), NewAnimClass);
    }
}

void AGGFWeapon::PlayCharacterAnimMontage(UAnimMontage* AnimMontage, float Duration) const
{
    // 유효성 검사
    if(AnimMontage == nullptr || FMath::IsNearlyZero(Duration)) return;

    // 캐릭터 애님 몽타주 재생
    if(GetOwner()->Implements<UGGFCharacterAnimationInterface>())
    {
        IGGFCharacterAnimationInterface::Execute_PlayAnimMontage(GetOwner(), AnimMontage, Duration);
    }
}
