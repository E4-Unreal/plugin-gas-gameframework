// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon\FireArm\GEFireArm.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"

AGEFireArm::AGEFireArm()
{
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
}

void AGEFireArm::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // 발사 간격 계산
    CalculateFireInterval();
}

void AGEFireArm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, MaxAmmo);
    DOREPLIFETIME(ThisClass, CurrentAmmo);
}


void AGEFireArm::Fire()
{
    // 발사 가능 여부 확인
    if(!CanFire()) return;

    // 서버에서 발사 실행
    ServerFire();
}

void AGEFireArm::ServerFire_Implementation()
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

void AGEFireArm::MulticastFire_Implementation()
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

void AGEFireArm::OnFire_Implementation()
{
    // TODO 자손 클래스에서 발사 로직 작성 (히트 스캔, 발사체)
}

void AGEFireArm::Reload()
{
    // 장전 가능 여부 확인
    if(!CanReload()) return;

    // 서버에서 장전 실행
    ServerReload();
}

void AGEFireArm::ServerReload_Implementation()
{
    // 장전 가능 여부 확인
    if(!CanReload()) return;
    bReloading = true;

    // 멀티캐스트
    MulticastReload();
}

void AGEFireArm::MulticastReload_Implementation()
{
    PlayAnimation(ReloadAnimation);
}

void AGEFireArm::FinishReloading()
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    bReloading = false;
}

void AGEFireArm::SetMaxAmmo(int32 Value)
{
    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // MaxAmmo 설정
    const int32 OldMaxAmmo = MaxAmmo;
    MaxAmmo = FMathf::Max(Value, 0);
    OnRep_MaxAmmo(OldMaxAmmo);
}

void AGEFireArm::SetCurrentAmmo(int32 Value)
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

void AGEFireArm::PlayAnimation(UAnimMontage* Animation) const
{
    if(SkeletalMesh && Animation)
        SkeletalMesh->PlayAnimation(Animation, false);
}

bool AGEFireArm::CanFire_Implementation()
{
    // 탄약 확인
    if(CurrentAmmo < AmmoToSpend) return false;

    // 아직 한 번도 발사하지 않은 경우
    if(LastFiredTime == 0) return true;

    // 발사 간격 확인
    return GetCurrentTime() - LastFiredTime >= FireInterval;
}

bool AGEFireArm::CanReload_Implementation()
{
    // 이미 재장전중인 상태입니다.
    if(bReloading) return false;

    // 탄약이 가득 찬 경우에는 재장전을 할 필요가 없습니다.
    return CurrentAmmo < MaxAmmo;
}

void AGEFireArm::SpendAmmo()
{
    SetCurrentAmmo(CurrentAmmo - FMath::Max(AmmoToSpend, 0));
}

float AGEFireArm::GetCurrentTime() const
{
    if(const UWorld* World = GetWorld())
    {
        return World->GetTimeSeconds();
    }

    return -1.f;
}

FVector AGEFireArm::GetMuzzleLocation() const
{
    return SkeletalMesh == nullptr ? GetActorLocation() : SkeletalMesh->GetSocketLocation(MuzzleSocketName);
}

void AGEFireArm::OnRep_MaxAmmo(int32 OldCurrentAmmo)
{
    OnMaxAmmoValueChanged.Broadcast(MaxAmmo);
}

void AGEFireArm::OnRep_CurrentAmmo(int32 OldCurrentAmmo)
{
    OnCurrentAmmoValueChanged.Broadcast(CurrentAmmo);
}
