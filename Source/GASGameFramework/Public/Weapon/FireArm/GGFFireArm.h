// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFWeapon.h"
#include "GGFFireArm.generated.h"

class USoundCue;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoValueChangedSiganature, int32, Ammo);

// TODO 리팩토링
/**
 * 캐릭터 애니메이션은 GameplayAbility에서 재생합니다.
 * 장전은 Reload > SetCurrentAmmo > FinishReloading 순으로 호출해야 합니다.
 * 총기 클래스를 작성할 떄 이 클래스를 상속받은 뒤 OnFire 메서드만 오버라이드하면 됩니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASGAMEFRAMEWORK_API AGGFFireArm : public AGGFWeapon
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
    TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

    /* 이벤트 */
    UPROPERTY(BlueprintAssignable)
    FOnAmmoValueChangedSiganature OnCurrentAmmoValueChanged;

    UPROPERTY(BlueprintAssignable)
    FOnAmmoValueChangedSiganature OnMaxAmmoValueChanged;

protected:
    // 총기 반동
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm")
    float RecoilWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm")
    FName ReloadNotifyName = "Reload";

    // 총구 소켓 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm", meta = (AllowPrivateAccess = true))
    FName MuzzleSocketName = "SOCKET_Muzzle";

    // 총기 최대 보유 탄약
    UPROPERTY(EditAnywhere, BlueprintGetter = GetMaxAmmo, Category = "Config|FireArm", ReplicatedUsing = OnRep_MaxAmmo)
    int32 MaxAmmo = 30;

    // 총기 현재 보유 탄약
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCurrentAmmo, Category = "State|FireArm", Transient, ReplicatedUsing = OnRep_CurrentAmmo)
    int32 CurrentAmmo;

    // 한 번 발사할 때마다 소비할 탄약 개수로 샷건처럼 여러 발을 동시에 발사하는 경우를 위한 설정입니다.
    UPROPERTY(EditAnywhere, BlueprintGetter = GetAmmoToSpend, Category = "Config|FireArm", ReplicatedUsing = OnRep_MaxAmmo)
    int32 AmmoToSpend = 1;

    // 분당 발사 횟수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm", meta = (AllowPrivateAccess = true))
    int32 RPM = 600;

    // 발사 간격 (초)
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetFireInterval, Category = "State|FireArm", Transient)
    float FireInterval;

    // 마지막으로 발사한 시간 (초)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|FireArm", meta = (AllowPrivateAccess = true), Transient)
    float LastFiredTime;

    // Reload 호출 시 true로 설정되며 FinishReloading 호출 시 false로 설정됩니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|FireArm", meta = (AllowPrivateAccess = true), Transient)
    bool bReloading;

    /* 애니메이션 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm|Animation", meta = (AllowPrivateAccess = true))
    TObjectPtr<UAnimMontage> FireAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm|Animation", meta = (AllowPrivateAccess = true))
    TObjectPtr<UAnimMontage> ReloadAnimation;

    // TODO 1인칭, 3인칭 구조체
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm|Animation", meta = (AllowPrivateAccess = true))
    TObjectPtr<UAnimMontage> CharacterFireAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm|Animation", meta = (AllowPrivateAccess = true))
    TObjectPtr<UAnimMontage> CharacterReloadAnimation;

    // TODO HitEffectDefinition처럼 데이터 에셋에서 처리
    /* SFX */
    // TODO 소음기
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm|Effect", meta = (AllowPrivateAccess = true))
    TObjectPtr<USoundCue> FireSound;

    /* VFX */
    // TODO 소염기
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm|Effect", meta = (AllowPrivateAccess = true))
    TObjectPtr<UParticleSystem> MuzzleFlash;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm|Effect", meta = (AllowPrivateAccess = true))
    FTransform MuzzleFlashTransform;

public:
    AGGFFireArm();

    virtual void PostInitializeComponents() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintNativeEvent, Category = "FireArm")
    bool CanFire();

    UFUNCTION(BlueprintNativeEvent, Category = "FireArm")
    bool CanReload();

    UFUNCTION(BlueprintCallable, Category = "FireArm")
    void Fire();

    UFUNCTION(BlueprintCallable, Category = "FireArm")
    void Reload();

    UFUNCTION(BlueprintCallable, Category = "FireArm")
    void FinishReloading();

    UFUNCTION(BlueprintSetter, Category = "FireArm")
    void SetMaxAmmo(int32 Value);

    UFUNCTION(BlueprintSetter, Category = "FireArm")
    void SetCurrentAmmo(int32 Value);

protected:
    /* Equipment */
    virtual void Activate_Implementation() override;
    virtual void Deactivate_Implementation() override;

    /* 가상 메서드 */

    UFUNCTION(Server, Reliable)
    void ServerFire();

    // 라인 트레이스, 총알 스폰 등의 발사 로직을 작성하는 곳으로 ServerFire에서 호출됩니다.
    UFUNCTION(BlueprintNativeEvent, Category = "FireArm")
    void OnFire();

    // 발사 애니메이션 재생 등 리플리케이트되지 않는 동작 정의
    UFUNCTION(NetMulticast, Reliable)
    virtual void MulticastFire();

    UFUNCTION(Server, Reliable)
    void ServerReload();

    UFUNCTION(NetMulticast, Reliable)
    void MulticastReload();

    // 무기 애니메이션을 재생합니다.
    UFUNCTION(BlueprintCallable, Category = "FireArm")
    void PlayAnimation(UAnimMontage* Animation) const;

    /* 메서드 */

    // CurrentAmmo에서 AmmoToSpend를 뺍니다.
    UFUNCTION(BlueprintCallable, Category = "FireArm")
    void SpendAmmo();

    // RPM으로부터 발사 간격(초)을 계산합니다.
    UFUNCTION(BlueprintCallable, Category = "FireArm")
    FORCEINLINE void CalculateFireInterval() { FireInterval = 60.f / RPM; }

    // 현재 시간(초)을 반환합니다.
    UFUNCTION(BlueprintPure, Category = "FireArm")
    float GetCurrentTime() const;

    // 총구 소켓의 위치를 반환합니다.
    // 총구 소켓을 찾지 못한 경우에는 액터 위치를 대신 반환합니다.
    UFUNCTION(BlueprintPure, Category = "FireArm")
    FVector GetMuzzleLocation() const;

    /* 이벤트 핸들링 */
    UFUNCTION()
    void OnPlayMontageNotifyBegin_Event(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_MaxAmmo(int32 OldCurrentAmmo);

    UFUNCTION()
    virtual void OnRep_CurrentAmmo(int32 OldCurrentAmmo);

public:
    /* Getter */
    UFUNCTION(BlueprintGetter)
    FORCEINLINE float GetFireInterval() const { return FireInterval; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetMaxAmmo() const { return MaxAmmo; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetAmmoToSpend() const { return AmmoToSpend; }
};
