// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HitEffect/GGFHitEffect_Niagara.h"

#include "NiagaraFunctionLibrary.h"

class UNiagaraComponent;

void UGGFHitEffect_Niagara::SpawnHitEffect(const FHitResult& HitResult) const
{
    // null 검사
    if(Niagara == nullptr) return;

    // HitResult 분석
    const FVector_NetQuantize& ImpactPoint = HitResult.ImpactPoint;
    const FRotator& ImpactRotator = FRotationMatrix::MakeFromZ(HitResult.ImpactNormal).Rotator();
    UPrimitiveComponent* TargetComponent = HitResult.GetComponent();

    // 스폰 정보 설정
    FFXSystemSpawnParameters SystemSpawnParameters;
    SystemSpawnParameters.SystemTemplate = Niagara;
    SystemSpawnParameters.AttachToComponent = TargetComponent;
    SystemSpawnParameters.Location = ImpactPoint;
    SystemSpawnParameters.Rotation = ImpactRotator;
    SystemSpawnParameters.Scale = Scale;

    // 나이아가라 시스템 스폰
    UNiagaraFunctionLibrary::SpawnSystemAttachedWithParams(SystemSpawnParameters);
}
