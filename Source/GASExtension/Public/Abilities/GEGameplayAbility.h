// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GEGameplayAbility.generated.h"

// TODO 기본 어빌리티와 입력 전용 어빌리티 분리
/**
 * 기본 인스턴스 정책 및 태그와 어빌리티 입력 설정이 적용된 게임플레이 어빌리티입니다.
 */
UCLASS()
class GASEXTENSION_API UGEGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

protected:
    // Ability InputID로 사용할 게임플레이 태그입니다.
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetInputTag, Category = "Config", meta = (Categories = "Input"))
    FGameplayTag InputTag;

public:
    UGEGameplayAbility();

    /* GameplayAbility */
    // 어빌리티 입력이 비활성화되면 어빌리티를 종료합니다.
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
    /* GameplayAbility */
    // Input Release 외의 조건으로 인해 어빌리티가 종료되는 경우 Input Release 상태로 자동 변경
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FGameplayTag& GetInputTag() const { return InputTag; }
};
