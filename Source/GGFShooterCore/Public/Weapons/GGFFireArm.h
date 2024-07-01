// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFWeapon.h"
#include "Data/GGFFireArmDefinition.h"
#include "GGFFireArm.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadFinishedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoValueChangedSiganature, int32, Ammo);

class UNiagaraComponent;
class USoundCue;

// TODO 리팩토링
/**
 * 캐릭터 애니메이션은 GameplayAbility에서 재생합니다.
 * 장전은 Reload > SetCurrentAmmo > FinishReloading 순으로 호출해야 합니다.
 * 총기 클래스를 작성할 떄 이 클래스를 상속받은 뒤 OnFire 메서드만 오버라이드하면 됩니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GGFSHOOTERCORE_API AGGFFireArm : public AGGFWeapon
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetAudioComponent, Category = "Component")
    TObjectPtr<UAudioComponent> AudioComponent;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetParticleSystem, Category = "Component")
    TObjectPtr<UParticleSystemComponent> ParticleSystem;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetNiagaraSystem, Category = "Component")
    TObjectPtr<UNiagaraComponent> NiagaraSystem;

public:
    /* 델리게이트 */

    UPROPERTY(BlueprintAssignable)
    FOnReloadFinishedSignature OnReloadFinished;

    UPROPERTY(BlueprintAssignable)
    FOnAmmoValueChangedSiganature OnCurrentAmmoValueChanged;

protected:

    // 총구 소켓 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FireArm")
    FName MuzzleSocketName = "Muzzle";

    // 총기 현재 보유 탄약
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCurrentAmmo, Category = "State|FireArm", Transient, ReplicatedUsing = OnRep_CurrentAmmo)
    int32 CurrentAmmo = 0;

    // 발사 간격 (초)
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetFireInterval, Category = "State|FireArm", Transient)
    float FireInterval = 0;

    // 마지막으로 발사한 시간 (초)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|FireArm", Transient)
    float LastFiredTime = 0;

    // Reload 호출 시 true로 설정되며 FinishReloading 호출 시 false로 설정됩니다.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|FireArm", Transient, ReplicatedUsing = OnRep_Reloading)
    bool bReloading = false;

    FTimerHandle ReloadTimerHandle;

    // 크로스헤어 위젯 인스턴스
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<UUserWidget> CrosshairWidget;

public:
    AGGFFireArm(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void BeginPlay() override;

    /* API */

    UFUNCTION(BlueprintNativeEvent, Category = "Fire")
    bool CanFire();

    UFUNCTION(BlueprintCallable, Category = "Fire")
    void Fire();

    UFUNCTION(BlueprintNativeEvent, Category = "Reload")
    bool CanReload();

    UFUNCTION(BlueprintCallable, Category = "Reload")
    void Reload();

    UFUNCTION(BlueprintCallable, Category = "Reload")
    void FinishReloading();

    UFUNCTION(BlueprintSetter, Category = "Reload")
    void SetCurrentAmmo(int32 Value);

    UFUNCTION(BlueprintPure, Category = "Reload")
    bool IsOutOfAmmo() const { return CurrentAmmo < GetFireArmData().AmmoToSpend; }

    UFUNCTION(BlueprintPure)
    const FGGFFireArmData& GetFireArmData() const;

protected:
    /* Equipment */

    virtual void OnIDUpdated(int32 NewID) override;
    virtual void Activate_Implementation() override;
    virtual void Deactivate_Implementation() override;

    /* 메서드 */

    // 크로스 헤어 UI 표시 및 숨기기
    UFUNCTION(BlueprintCallable)
    virtual void ShowCrosshair(bool bShow);

    UFUNCTION(Server, Reliable, Category = "Fire")
    void ServerFire();

    // 라인 트레이스, 총알 스폰 등의 발사 로직을 작성하는 곳으로 ServerFire에서 호출됩니다.
    UFUNCTION(BlueprintNativeEvent, Category = "Fire")
    void OnFire();

    // 발사 애니메이션 재생 등 리플리케이트되지 않는 동작 정의
    UFUNCTION(NetMulticast, Reliable, Category = "Fire")
    virtual void MulticastFire();

    UFUNCTION(Server, Reliable, Category = "Reload")
    void ServerReload();

    UFUNCTION(NetMulticast, Reliable, Category = "Reload")
    void MulticastReload();

    // 총기 발사 애니메이션 재생
    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void PlayFireAnimMontage() const;

    // 총기 재장전 애니메이션 재생
    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void PlayReloadAnimMontage() const;

    // CurrentAmmo에서 AmmoToSpend를 뺍니다.
    UFUNCTION(BlueprintCallable, Category = "Fire")
    void SpendAmmo();

    // RPM으로부터 발사 간격(초)을 계산합니다.
    UFUNCTION(BlueprintCallable, Category = "Fire")
    FORCEINLINE void CalculateFireInterval() { FireInterval = 60.f / GetFireArmData().RPM; }

    // 현재 시간(초)을 반환합니다.
    UFUNCTION(BlueprintPure, Category = "Fire")
    float GetCurrentTime() const;

    // 총구 소켓의 위치를 반환합니다.
    // 총구 소켓을 찾지 못한 경우에는 액터 위치를 대신 반환합니다.
    UFUNCTION(BlueprintPure, Category = "Fire")
    FVector GetMuzzleLocation() const;

    /* 리플리케이트 */

    UFUNCTION()
    virtual void OnRep_CurrentAmmo(int32 OldCurrentAmmo);

    UFUNCTION()
    virtual void OnRep_Reloading(bool OldReloading);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UAudioComponent* GetAudioComponent() const { return AudioComponent; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UParticleSystemComponent* GetParticleSystem() const { return ParticleSystem; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UNiagaraComponent* GetNiagaraSystem() const { return NiagaraSystem; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE float GetFireInterval() const { return FireInterval; }

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetCurrentAmmo() const { return CurrentAmmo; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetMaxAmmo() const { return GetFireArmData().MaxAmmo; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE float GetCameraMultiplier() const { return GetFireArmData().CameraMultiplier; }
};
