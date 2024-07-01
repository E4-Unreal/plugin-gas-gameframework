// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/GGFFireArm.h"

#include "NiagaraComponent.h"
#include "Abilities/GGFGA_ADS.h"
#include "Abilities/GGFGA_AutoReload.h"
#include "Abilities/GGFGA_Fire.h"
#include "Abilities/GGFGA_Reload.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Components/GGFEquipmentDataManager.h"
#include "Components/GGFFireArmDataManager.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

AGGFFireArm::AGGFFireArm(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UGGFFireArmDataManager>(DataManagerName))
{
    /* AudioComponent */
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(GetSkeletalMesh(), MuzzleSocketName);
    AudioComponent->bAutoActivate = false;

    /* ParticleSystem */
    ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
    ParticleSystem->SetupAttachment(GetSkeletalMesh(), MuzzleSocketName);
    ParticleSystem->bAutoActivate = false;

    /* NiagaraSystem */
    NiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"));
    NiagaraSystem->SetupAttachment(GetSkeletalMesh(), MuzzleSocketName);
    NiagaraSystem->bAutoActivate = false;

    /* 기본 설정 */

    // 어빌리티
    ActiveAbilities.Emplace(UGGFGA_Fire::StaticClass());
    ActiveAbilities.Emplace(UGGFGA_Reload::StaticClass());
    ActiveAbilities.Emplace(UGGFGA_ADS::StaticClass());
    ActiveAbilities.Emplace(UGGFGA_AutoReload::StaticClass());
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
    DOREPLIFETIME(ThisClass, bReloading);
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

void AGGFFireArm::OnFire_Implementation()
{
    // TODO 자손 클래스에서 발사 로직 작성 (히트 스캔, 발사체)
}

void AGGFFireArm::MulticastFire_Implementation()
{
    const auto& FireArmData = GetFireArmData();

    // 발사 몽타주 재생
    PlayFireAnimMontage();

    // 발사 VFX
    if(GetNiagaraSystem()->GetAsset())
    {
        GetNiagaraSystem()->Activate(true);
    }
    else
    {
        GetParticleSystem()->Activate(true);
    }

    // 발사 SFX
    if(GetAudioComponent()->IsPlaying())
    {
        /*
         * 단일 오디오 컴포넌트로 높은 RPM의 소리 재생 시 버벅입니다.
         * 여러 오디오 컴포넌트를 부착하고 번갈아가며 재생하는 방법도 있지만,
         * 그것보다는 루프 버전 소리를 재생하거나 스폰하는 것이 더 나을 것 같아 이렇게 작성하였습니다.
         */
        UGameplayStatics::SpawnSoundAttached(
            FireArmData.FireSound,
            GetSkeletalMesh(),
            MuzzleSocketName
            );
    }
    else
    {
        GetAudioComponent()->Play();
    }
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

    // 데이터 가져오기
    const auto& FireArmData = GetFireArmData();

    // 재장전 타이머 설정
    GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &ThisClass::FinishReloading, FireArmData.ReloadDuration);

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
    // 타이머 핸들 초기화
    ReloadTimerHandle.Invalidate();

    // ServerReload가 먼저 호출되어야 합니다.
    if(!bReloading) return;

    // 총알을 채웁니다
    SetCurrentAmmo(GetMaxAmmo());

    // 재장전 상태 해제
    bReloading = false;

    // 델리게이트 호출
    OnReloadFinished.Broadcast();
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

    // 변수 선언
    const auto& FireArmData = GetFireArmData();
    FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

    // AudioComponent
    GetAudioComponent()->AttachToComponent(GetSkeletalMesh(), AttachmentTransformRules, MuzzleSocketName);
    GetAudioComponent()->SetSound(FireArmData.FireSound);

    // ParticleSystem
    GetParticleSystem()->AttachToComponent(GetSkeletalMesh(), AttachmentTransformRules, MuzzleSocketName);
    GetParticleSystem()->SetTemplate(FireArmData.MuzzleParticle);

    // NiagaraSystem
    GetNiagaraSystem()->AttachToComponent(GetSkeletalMesh(), AttachmentTransformRules, MuzzleSocketName);
    GetNiagaraSystem()->SetAsset(FireArmData.MuzzleSystem);

    // RPM 재계산
    CalculateFireInterval();
}

void AGGFFireArm::Activate_Implementation()
{
    Super::Activate_Implementation();

    ShowCrosshair(true);
}

void AGGFFireArm::Deactivate_Implementation()
{
    ShowCrosshair(false);

    Super::Deactivate_Implementation();
}

void AGGFFireArm::ShowCrosshair(bool bShow)
{
    // 유효성 검사
    if(GetFireArmData().CrosshairWidget == nullptr) return;

    // 로컬 플레이어 UI 표시
    if(APawn* OwnerPawn = Cast<APawn>(GetOwner()))
    {
        if(OwnerPawn->IsPlayerControlled() && OwnerPawn->IsLocallyControlled())
        {
            if(bShow)
            {
                if(CrosshairWidget == nullptr)
                {
                    CrosshairWidget = CreateWidget(CastChecked<APlayerController>(OwnerPawn->Controller), GetFireArmData().CrosshairWidget);
                }

                CrosshairWidget->AddToViewport();
            }
            else if(CrosshairWidget)
            {
                CrosshairWidget->RemoveFromParent();
            }
        }
    }
}

bool AGGFFireArm::CanFire_Implementation()
{
    // 장비 장착 중에는 불가
    if(bEquipping) return false;

    // 재장전 중에는 불가
    if(bReloading) return false;

    // 탄약 확인
    if(IsOutOfAmmo()) return false;

    // 아직 한 번도 발사하지 않은 경우
    if(LastFiredTime == 0) return true;

    // 마지막 발사 시점으로부터 경과한 시간
    const float DeltaTime = GetCurrentTime() - LastFiredTime;

    // 발사 간격 확인 (단발광클 1위 광클 속도가 0.094초라고 합니다.오차 범위를 이 수치 이하까지는 적용해도 문제없을 듯 합니다.)
    return DeltaTime > FireInterval || FMath::IsNearlyEqual(DeltaTime, FireInterval, 0.02f);
}

bool AGGFFireArm::CanReload_Implementation()
{
    // 장비 장착 중에는 불가
    if(bEquipping) return false;

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
    PlayCharacterAnimMontage(FireArmData.CharacterReloadMontage, FireArmData.ReloadDuration);
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

void AGGFFireArm::OnRep_Reloading(bool OldReloading)
{
    if(bReloading)
    {
        OnReloadFinished.Broadcast();
    }
}

const FGGFFireArmData& AGGFFireArm::GetFireArmData() const
{
    return CastChecked<UGGFFireArmDataManager>(GetDataManager())->GetFireArmData();
}
