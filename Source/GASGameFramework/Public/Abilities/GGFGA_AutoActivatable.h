// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GEPlayerAbility.h"
#include "GGFGA_AutoActivatable.generated.h"

// TODO 필요없다고 판단되면 삭제될 수 있습니다.
/**
 * Ability가 부여되는 즉시 자동으로 발동시키거나 소멸시킬 수 있는 GameplayAbility 클래스입니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFGA_AutoActivatable : public UGEPlayerAbility
{
    GENERATED_BODY()

    // true 설정 시 Ability가 부여되는 즉시 해당 Ability를 발동합니다.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    bool bActivateAbilityOnGranted = true;

    // true 설정 시 Ability가 종료되는 즉시 해당 Ability를 제거합니다.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    bool bRemoveAfterActivation = true;

public:
    /* UGameplayAbility */

    virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
