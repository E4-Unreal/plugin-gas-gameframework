// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/GGFFireArm.h"

#include "Components/GGFEquipmentDataManager.h"
#include "Components/GGFFireArmDataManager.h"
#include "Data/GGFEquipmentDefinition.h"
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

    // TODO 삼인칭 애니메이션
    // 캐릭터 애니메이션 재생
    PlayCharacterMontage(CharacterFireAnimation);

    // 파티클 시스템 스폰
    UGameplayStatics::SpawnEmitterAttached(
            MuzzleFlash,
            GetSkeletalMesh(),
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

    // TODO 리팩토링
    // 재장전 애니메이션이 설정되지 않았거나 노티파이가 설정되지 않은 경우에는 즉시 재장전을 실행합니다.
    if(CharacterReloadAnimation == nullptr)
    {
        FinishReloading();
    }
    else
    {
        bool bReloadNotifyExist = false;
        const TArray<FAnimNotifyEvent>& Notifies = CharacterReloadAnimation->Notifies;
        for (const FAnimNotifyEvent& Notify : Notifies)
        {
            // null 검사
            if(Notify.Notify == nullptr) continue;

            // 노티파이 이름 검사
            if(FName(*Notify.Notify->GetNotifyName()).IsEqual(ReloadNotifyName))
            {
                bReloadNotifyExist = true;
                break;
            }
        }

        if(!bReloadNotifyExist) FinishReloading();
    }

    // 멀티캐스트
    MulticastReload();
}

void AGGFFireArm::MulticastReload_Implementation()
{
    PlayAnimation(ReloadAnimation);

    // TODO 삼인칭 애니메이션
    // 캐릭터 애니메이션 재생
    PlayCharacterMontage(CharacterReloadAnimation);
}

void AGGFFireArm::FinishReloading()
{
    // ServerReload가 먼저 호출되어야 합니다.
    if(!bReloading) return;

    // 서버에서만 호출 가능합니다.
    if(!HasAuthority()) return;

    // 총알을 채웁니다
    SetCurrentAmmo(MaxAmmo);

    // 재장전 상태 해제
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

    // CurrentAmmo 설정
    const int32 OldCurrentAmmo = CurrentAmmo;
    CurrentAmmo = FMath::Clamp(Value, 0, MaxAmmo);
    OnRep_CurrentAmmo(OldCurrentAmmo);
}

void AGGFFireArm::Activate_Implementation()
{
    Super::Activate_Implementation();

    // 서버에서만 재장전 가능
    if(HasAuthority())
    {
        // TODO 재장전 애님 노티파이 이벤트 바인딩
        /*if(UAnimInstance* LocalFirstPersonAnimInstance = GetFirstPersonAnimInstance())
            LocalFirstPersonAnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::OnPlayMontageNotifyBegin_Event);*/
    }
}

void AGGFFireArm::Deactivate_Implementation()
{
    Super::Deactivate_Implementation();

    // 서버에서만 재장전 가능
    if(HasAuthority())
    {
        // TODO 재장전 애님 노티파이 이벤트 언바인딩
        /*if(UAnimInstance* LocalFirstPersonAnimInstance = GetFirstPersonAnimInstance())
            LocalFirstPersonAnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &ThisClass::OnPlayMontageNotifyBegin_Event);*/
    }
}

void AGGFFireArm::OnIDUpdated(int32 NewID)
{
    Super::OnIDUpdated(NewID);

    const auto& FireArmData = CastChecked<UGGFFireArmDataManager>(GetDataManager());
}

void AGGFFireArm::PlayAnimation(UAnimMontage* Animation) const
{
    if(GetSkeletalMesh() && Animation)
        GetSkeletalMesh()->PlayAnimation(Animation, false);
}

bool AGGFFireArm::CanFire_Implementation()
{
    // 탄약 확인
    if(CurrentAmmo < AmmoToSpend) return false;

    // 아직 한 번도 발사하지 않은 경우
    if(LastFiredTime == 0) return true;

    // 마지막 발사 시점으로부터 경과한 시간
    const float DeltaTime = GetCurrentTime() - LastFiredTime;

    // 발사 간격 확인
    return DeltaTime > FireInterval || FMath::IsNearlyEqual(DeltaTime, FireInterval, 1E-04);
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
    return GetSkeletalMesh() == nullptr ? GetActorLocation() : GetSkeletalMesh()->GetSocketLocation(MuzzleSocketName);
}

void AGGFFireArm::OnPlayMontageNotifyBegin_Event(FName NotifyName,
    const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    // 노티파이 이름 검사
    if(!NotifyName.IsEqual(ReloadNotifyName)) return;

    // 재장전
    FinishReloading();
}

void AGGFFireArm::OnRep_MaxAmmo(int32 OldCurrentAmmo)
{
    OnMaxAmmoValueChanged.Broadcast(MaxAmmo);
}

void AGGFFireArm::OnRep_CurrentAmmo(int32 OldCurrentAmmo)
{
    OnCurrentAmmoValueChanged.Broadcast(CurrentAmmo);
}
