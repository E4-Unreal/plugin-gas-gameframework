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

    // 인터페이스 검사
    if(!GetOwner()->Implements<UGGFCharacterAnimationInterface>()) return;

    // 무기 데이터
    auto WeaponDataManager = CastChecked<UGGFWeaponDataManager>(GetDataManager());
    const auto& Data = WeaponDataManager->GetWeaponData();

    // 캐릭터 애니메이션 클래스 변경
    IGGFCharacterAnimationInterface::Execute_SetAnimInstanceClass(GetOwner(), Data.CharacterAnimClass);

    // 장비 장착 몽타주 재생
    PlayCharacterMontage(Data.EquipMontage, Data.EquipDuration);
}

void AGGFWeapon::Deactivate_Implementation()
{
    Super::Deactivate_Implementation();

    // 인터페이스 검사
    if(!GetOwner()->Implements<UGGFCharacterAnimationInterface>()) return;

    // 무기 데이터
    auto WeaponDataManager = CastChecked<UGGFWeaponDataManager>(GetDataManager());
    const auto& Data = WeaponDataManager->GetWeaponData();

    // 장비 장착 해제 몽타주 재생
    PlayCharacterMontage(Data.UnequipMontage, Data.UnequipDuration);
}

void AGGFWeapon::PlayCharacterMontage(UAnimMontage* MontageToPlay, float Duration)
{
    // 유효성 검사
    if(MontageToPlay == nullptr || FMath::IsNearlyZero(Duration)) return;

    // 인터페이스 검사
    if(!GetOwner()->Implements<UGGFCharacterAnimationInterface>()) return;

    // 몽타주 재생
    float PlayRate = MontageToPlay->GetPlayLength() / Duration;
    IGGFCharacterAnimationInterface::Execute_PlayAnimMontage(GetOwner(), MontageToPlay, PlayRate);
}

void AGGFWeapon::OnIDUpdated(int32 NewID)
{
    // 무기 데이터
    auto WeaponDataManager = CastChecked<UGGFWeaponDataManager>(GetDataManager());
    const auto& Data = WeaponDataManager->GetWeaponData();
    GetSkeletalMesh()->SetAnimClass(Data.WeaponAnimClass);

    Super::OnIDUpdated(NewID);
}
