// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEGameplayAbility.h"
#include "GEGA_Montage.generated.h"

USTRUCT(BlueprintType)
struct FGEMontageConfig
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
    TObjectPtr<UAnimMontage> MontageToPlay;

    UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
    float PlayRate = 1.f;

    UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
    FName SectionName;
};

/**
 * 어빌리티에서 몽타주 재생은 자주 쓰이기 때문에 기본 구현해두었습니다.
 * GameplayAbility_Montage와 차이점은 GECharacterMeshInterface를 사용하여 1인칭, 3인칭 애니메이션을 각각 재생할 수 있습니다.
 */
UCLASS(Abstract)
class GASGAMEFRAMEWORK_API UGEGA_Montage : public UGEGameplayAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FGEMontageConfig FirstPersonMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FGEMontageConfig ThirdPersonMontage;

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
    UFUNCTION(BlueprintCallable)
    void PlayMontage(USkeletalMeshComponent* Mesh, const FGEMontageConfig& MontageConfig);
};
