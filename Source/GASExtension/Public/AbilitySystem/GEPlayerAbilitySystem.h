// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEDamageableAbilitySystem.h"
#include "GEPlayerAbilitySystem.generated.h"

/**
 * 플레이어 캐릭터 전용 ASC로 어빌리티 입력 관련 기능이 포함되어 있습니다.
 */
UCLASS()
class GASEXTENSION_API UGEPlayerAbilitySystem : public UGEDamageableAbilitySystem
{
    GENERATED_BODY()

public:
    /* API */

    // 입력 태그로 Ability를 Press합니다.
    UFUNCTION(BlueprintCallable, Category = "GGFAbilitySystemBase")
    void PressInputTag(FGameplayTag InputTag);

    // 입력 태그로 Ability를 Release합니다.
    UFUNCTION(BlueprintCallable, Category = "GGFAbilitySystemBase")
    void ReleaseInputTag(FGameplayTag InputTag);

protected:
    /* AbilitySystemComponent */

    // Ability InputTag가 설정된 Ability의 경우 InputID를 설정합니다.
    virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

    /* GEAbilitySystem */

    virtual void OnAbilitySpecDirtied(const FGameplayAbilitySpec& AbilitySpec) override;
};
