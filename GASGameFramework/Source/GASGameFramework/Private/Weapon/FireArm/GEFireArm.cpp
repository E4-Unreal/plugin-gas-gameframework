﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon\FireArm\GGFFireArm.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

AGGFFireArm::AGGFFireArm()
{
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
}

void AGGFFireArm::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 발사 간격 계산
    CalculateFireInterval();
}

void AGGFFireArm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, MaxAmmo);
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
    // 무기 애니메이션 재생
    PlayAnimation(FireAnimation);

    // 캐릭터 애니메이션 재생
    if(UAnimInstance* ThirdPersonAnimInstance = GetThirdPersonAnimInstance())
    {
        ThirdPersonAnimInstance->Montage_Play(CharacterFireAnimation);
    }

    if(UAnimInstance* FirstPersonAnimInstance = GetFirstPersonAnimInstance())
    {
        FirstPersonAnimInstance->Montage_Play(CharacterFireAnimation);
    }

    // 파티클 시스템 스폰
    UGameplayStatics::SpawnEmitterAttached(
            MuzzleFlash,
            SkeletalMesh,
            MuzzleSocketName,
            MuzzleFlashTransform.GetLocation(),
            MuzzleFlashTransform.GetRotation().Rotator(),
            MuzzleFlashTransform.GetScale3D()
            );

    // 소리 재생
    UGameplayStatics::PlaySoundAtLocation(
        this,
        FireSound,
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

    // 멀티캐스트
    MulticastReload();
}

void AGGFFireArm::MulticastReload_Implementation()
{
    PlayAnimation(ReloadAnimation);
}

void AGGFFireArm::FinishReloading()
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    bReloading = false;
}

void AGGFFireArm::SetMaxAmmo(int32 Value)
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // MaxAmmo 설정
    const int32 OldMaxAmmo = MaxAmmo;
    MaxAmmo = FMathf::Max(Value, 0);
    OnRep_MaxAmmo(OldMaxAmmo);
}

void AGGFFireArm::SetCurrentAmmo(int32 Value)
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // 재장전을 통해서만 설정이 가능합니다.
    if(!bReloading) return;

    // CurrentAmmo 설정
    const int32 OldCurrentAmmo = CurrentAmmo;
    CurrentAmmo = FMath::Clamp(Value, 0, MaxAmmo);
    OnRep_CurrentAmmo(OldCurrentAmmo);
}

void AGGFFireArm::PlayAnimation(UAnimMontage* Animation) const
{
    if(SkeletalMesh && Animation)
        SkeletalMesh->PlayAnimation(Animation, false);
}

bool AGGFFireArm::CanFire_Implementation()
{
    // 탄약 확인
    if(CurrentAmmo < AmmoToSpend) return false;

    // 아직 한 번도 발사하지 않은 경우
    if(LastFiredTime == 0) return true;

    // 발사 간격 확인
    return GetCurrentTime() - LastFiredTime >= FireInterval;
}

bool AGGFFireArm::CanReload_Implementation()
{
    // 이미 재장전중인 상태입니다.
    if(bReloading) return false;

    // 탄약이 가득 찬 경우에는 재장전을 할 필요가 없습니다.
    return CurrentAmmo < MaxAmmo;
}

void AGGFFireArm::SpendAmmo()
{
    SetCurrentAmmo(CurrentAmmo - FMath::Max(AmmoToSpend, 0));
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
    return SkeletalMesh == nullptr ? GetActorLocation() : SkeletalMesh->GetSocketLocation(MuzzleSocketName);
}

void AGGFFireArm::OnRep_MaxAmmo(int32 OldCurrentAmmo)
{
    OnMaxAmmoValueChanged.Broadcast(MaxAmmo);
}

void AGGFFireArm::OnRep_CurrentAmmo(int32 OldCurrentAmmo)
{
    OnCurrentAmmoValueChanged.Broadcast(CurrentAmmo);
}
