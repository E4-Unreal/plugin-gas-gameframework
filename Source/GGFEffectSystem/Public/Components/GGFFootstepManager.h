// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGFFootstepManager.generated.h"

class UGGFEffectDefinition;

/**
 * 발 스텝 전용 이펙트 매니저
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class GGFEFFECTSYSTEM_API UGGFFootstepManager : public UActorComponent
{
    GENERATED_BODY()

protected:
    /* 레퍼런스 */

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TObjectPtr<USkeletalMeshComponent> TargetMesh;

public:
    /* 프로퍼티 */

    // 기본 발 스텝 이펙트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FX")
    TObjectPtr<UGGFEffectDefinition> DefaultFootstepEffect;

    // 표면 종류에 따른 발 스텝 이펙트 매핑 정보
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|FX")
    TMap<TEnumAsByte<EPhysicalSurface>, TObjectPtr<UGGFEffectDefinition>> FootstepEffectMap;

    // 왼 발 스텝 소켓 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Mesh")
    FName LeftFootstepSocketName = "ball_l";

    // 오른 발 스텝 소켓 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Mesh")
    FName RightFootstepSocketName = "ball_r";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Trace")
    TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Trace")
    float TraceRange = 20;

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Debug")
    bool bShowDebug = false;
#endif

public:
    UGGFFootstepManager();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetMesh(USkeletalMeshComponent* NewTargetMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnLeftFootstepEffect() const;

    UFUNCTION(BlueprintCallable)
    virtual void SpawnRightFootstepEffect() const;

    UFUNCTION(BlueprintCallable)
    virtual void SpawnFootstepEffect(FName FootstepSocketName) const;

protected:
    /* Getter */

    UFUNCTION(BlueprintPure)
    FORCEINLINE USkeletalMeshComponent* GetTargetMesh() const { return TargetMesh; }
};
