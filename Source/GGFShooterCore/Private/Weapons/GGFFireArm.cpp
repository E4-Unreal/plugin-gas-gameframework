// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/GGFFireArm.h"

#include "Components/GGFEquipmentDataManager.h"
#include "Components/GGFFireArmDataManager.h"
#include "Interfaces/GGFCharacterAnimationInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

AGGFFireArm::AGGFFireArm(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGGFFireArmDataManager>(DataManagerName))
{

}

void AGGFFireArm::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 발사 간격 계산
    CalculateFireInterval();
}

void AGGFFireArm::BeginPlay()
{
    Super::BeginPlay();

    SetCurrentAmmo(GetMaxAmmo());
}

void AGGFFireArm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, CurrentAmmo);
}


void AGGFFireArm::Fire()
{
    // 발사 가능 여부 확인
    if(!CanFire()) return;

    // 서버에서 발사 실행
    ServerFire();
}

void AGGFFireArm::ServerFire_Implementation()
{
    // 발사 가능 여부 확인
    if(!CanFire()) return;

    // 발사 시간 기록
    LastFiredTime = GetCurrentTime();

    // 탄약 소비
    SpendAmmo();

    // 발사
    OnFire();

    // 멀티캐스트
    MulticastFire();
}

void AGGFFireArm::MulticastFire_Implementation()
{
    const auto& FireArmData = GetFireArmData();

    // 발사 몽타주 재생
    PlayFireAnimMontage();

    // 파티클 시스템 스폰
    UGameplayStatics::SpawnEmitterAttached(
            FireArmData.MuzzleParticle,
            GetSkeletalMesh(),
            MuzzleSocketName,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            FVector::OneVector
            );

    // 소리 재생
    UGameplayStatics::PlaySoundAtLocation(
        this,
        FireArmData.FireSound,
        GetMuzzleLocation(),
        FRotator::ZeroRotator
        );
}

void AGGFFireArm::OnFire_Implementation()
{
    // TODO 자손 클래스에서 발사 로직 작성 (히트 스캔, 발사체)
}

void AGGFFireArm::Reload()
{
    // 장전 가능 여부 확인
    if(!CanReload()) return;

    // 서버에서 장전 실행
    ServerReload();
}

void AGGFFireArm::ServerReload_Implementation()
{
    // 장전 가능 여부 확인
    if(!CanReload()) return;
    bReloading = true;

    if(GetOwner()->Implements<UGGFCharacterAnimationInterface>())
    {
        const auto& FireArmData = GetFireArmData();
        IGGFCharacterAnimationInterface::Execute_PlayAnimMontage(GetOwner(), FireArmData.CharacterReloadMontage, FireArmData.ReloadDuration);
    }

    // 멀티캐스트
    MulticastReload();
}

void AGGFFireArm::MulticastReload_Implementation()
{
    // 재장전 몽타주 재생
    PlayReloadAnimMontage();
}

void AGGFFireArm::FinishReloading()
{
    // ServerReload가 먼저 호출되어야 합니다.
    if(!bReloading) return;

    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // 총알을 채웁니다
    SetCurrentAmmo(GetMaxAmmo());

    // 재장전 상태 해제
    bReloading = false;
}

void AGGFFireArm::SetCurrentAmmo(int32 Value)
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // CurrentAmmo 설정
    const int32 OldCurrentAmmo = CurrentAmmo;
    CurrentAmmo = FMath::Clamp(Value, 0, GetMaxAmmo());
    OnRep_CurrentAmmo(OldCurrentAmmo);
}

void AGGFFireArm::OnIDUpdated(int32 NewID)
{
    Super::OnIDUpdated(NewID);

    const auto& FireArmData = CastChecked<UGGFFireArmDataManager>(GetDataManager());
}

bool AGGFFireArm::CanFire_Implementation()
{
    // 탄약 확인
    if(CurrentAmmo < GetFireArmData().AmmoToSpend) return false;

    // 아직 한 번도 발사하지 않은 경우
    if(LastFiredTime == 0) return true;

    // 마지막 발사 시점으로부터 경과한 시간
    const float DeltaTime = GetCurrentTime() - LastFiredTime;

    // 발사 간격 확인 (단발광클 1위 광클 속도가 0.094초라고 합니다.오차 범위를 이 수치 이하까지는 적용해도 문제없을 듯 합니다.)
    return DeltaTime > FireInterval || FMath::IsNearlyEqual(DeltaTime, FireInterval, 0.02f);
}

bool AGGFFireArm::CanReload_Implementation()
{
    // 이미 재장전중인 상태입니다.
    if(bReloading) return false;

    // 탄약이 가득 찬 경우에는 재장전을 할 필요가 없습니다.
    return CurrentAmmo < GetMaxAmmo();
}

void AGGFFireArm::PlayFireAnimMontage() const
{
    const auto& FireArmData = GetFireArmData();

    PlayAnimMontage(FireArmData.FireMontage, FireInterval);
    PlayCharacterAnimMontage(FireArmData.CharacterFireMontage, FireInterval);
}

void AGGFFireArm::PlayReloadAnimMontage() const
{
    const auto& FireArmData = GetFireArmData();

    PlayAnimMontage(FireArmData.ReloadMontage, FireArmData.ReloadDuration);
    PlayCharacterAnimMontage(FireArmData.CharacterFireMontage, FireArmData.ReloadDuration);
}

void AGGFFireArm::SpendAmmo()
{
    SetCurrentAmmo(CurrentAmmo - FMath::Max(GetFireArmData().AmmoToSpend, 0));
}

float AGGFFireArm::GetCurrentTime() const
{
    if(const UWorld* World = GetWorld())
    {
        return World->GetTimeSeconds();
    }

    return -1.f;
}

FVector AGGFFireArm::GetMuzzleLocation() const
{
    return GetSkeletalMesh() == nullptr ? GetActorLocation() : GetSkeletalMesh()->GetSocketLocation(MuzzleSocketName);
}

void AGGFFireArm::OnRep_CurrentAmmo(int32 OldCurrentAmmo)
{
    OnCurrentAmmoValueChanged.Broadcast(CurrentAmmo);
}

FGGFFireArmData AGGFFireArm::GetFireArmData() const
{
    auto FireArmDataManager = CastChecked<UGGFFireArmDataManager>(GetDataManager());
    return FireArmDataManager->GetFireArmData();
}
