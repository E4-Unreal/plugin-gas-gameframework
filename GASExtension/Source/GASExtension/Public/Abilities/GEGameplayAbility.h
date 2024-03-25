// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEAbilityInputTagInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GEGameplayAbility.generated.h"

/**
 * 기본 인스턴스 정책 및 태그와 어빌리티 입력 설정이 적용된 게임플레이 어빌리티입니다.
 * 필요한 경우가 아닌 이상 이 어빌리티 클래스를 상속받아 사용할 것을 권장드리며 불가피한 경우
 * 해당 어빌리티 클래스에 IGEAbilityInputTagInterface를 구현하셔야 어빌리티 입력 시스템이 정상적으로 동작합니다.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GASEXTENSION_API UGEGameplayAbility : public UGameplayAbility, public IGEAbilityInputTagInterface
{
    GENERATED_BODY()

    // GEAbilitySystemBase에서 Ability InputID로 사용할 게임플레이 태그입니다.
    UPROPERTY(EditAnywhere, Category = "Config")
    FGameplayTag InputTag;

public:
    UGEGameplayAbility();

    /* GameplayAbility */
    // 기본적으로 입력이 Release되면 어빌리티는 종료됩니다.
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
    // Input Release 외의 조건으로 인해 어빌리티가 종료되는 경우 Input Release 상태로 변경
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
    /* GEAbilityInputTagInterface 인터페이스 */
    virtual const FGameplayTag GetInputTag_Implementation() const override;
};
