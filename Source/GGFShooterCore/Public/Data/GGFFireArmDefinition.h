﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDefinitionBase.h"
#include "GGFFireArmDefinition.generated.h"

class AGGFProjectile;
class UNiagaraSystem;
class USoundCue;

/**
 * 장비 정의를 위한 데이터 테이블 구조체
 */
USTRUCT()
struct GGFSHOOTERCORE_API FGGFFireArmData : public FGGFDataTableRowBase
{
    GENERATED_BODY()

    static const FGGFFireArmData EmptyFireArmData;

    // 총기 발사 방식 (히트 스캔)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    bool bUseHitScan = false;

    // 총기 발사 방식 (연사)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    bool bAutomatic = true;

    // 분당 발사 횟수
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec", meta = (ClampMin = 1))
    int32 RPM = 600;

    // 최대 탄약 수
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec", meta = (ClampMin = 1))
    int32 MaxAmmo = 30;

    // 1회 발사 시 소모 탄약 수
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec", meta = (ClampMin = 1))
    int32 AmmoToSpend = 1;

    // 1회 발사 시 발사되는 펠릿 수 (주로 샷건에서 사용)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec", meta = (ClampMin = 1))
    int32 PelletNum = 1;

    // 총기 반동 (수평, 수직)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    FVector2D Recoil;

    // 탄 분산 (수평, 수직)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    FVector2D Spread;

    // 탄 분산 (수평, 수직)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    TSubclassOf<AGGFProjectile> DefaultProjectile;

    // 재장전 시간
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    float ReloadDuration = 2.5f;

    // 카메라 확대 배율
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spec")
    float CameraMultiplier = 1.5f;

    // 총기 발사음
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
    TObjectPtr<USoundCue> FireSound;

    // 총기 발사음 (소음기)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
    TObjectPtr<USoundCue> SilencerFireSound;

    // 총구 이펙트 (캐스케이드)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    TObjectPtr<UParticleSystem> MuzzleParticle;

    // 총구 이펙트 (나이아가라)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    TObjectPtr<UNiagaraSystem> MuzzleSystem;

    // 총기 발사 애니메이션 (총기)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|FireArm")
    TObjectPtr<UAnimMontage> FireMontage;

    // 총기 재장전 애니메이션 (총기)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|FireArm")
    TObjectPtr<UAnimMontage> ReloadMontage;

    // 총기 발사 애니메이션 (캐릭터)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Character")
    TObjectPtr<UAnimMontage> CharacterFireMontage;

    // 총기 재장전 애니메이션 (캐릭터)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Character")
    TObjectPtr<UAnimMontage> CharacterReloadMontage;

    // 크로스헤어
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> CrosshairWidget;

    // 기본 생성자
    FGGFFireArmData() { }
};

/**
 * 총기 전용 데이터 에셋
 */
UCLASS(BlueprintType, Blueprintable)
class GGFSHOOTERCORE_API UGGFFireArmDefinition : public UGGFDefinitionBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FGGFFireArmData Data;

public:
    /* GGFDefinitionBase */

    virtual bool InitFromDataTableRowBase(FGGFDataTableRowBase* NewDataTableRowBase) override;

    /* Getter */

    UFUNCTION(BlueprintGetter)
    const FGGFFireArmData& GetData() const { return Data; }
};
