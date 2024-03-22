// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "GEAnimInstance.generated.h"

class UAbilitySystemComponent;

/**
 * 게임플레이 태그와 애님 인스턴스 프로퍼티 바인딩 기능이 포함된 클래스입니다.
 * TagsToRegister에서 감지할 게임플레이 태그 이벤트를 설정하고 OnGameplayEffectTagCountChanged_Event에서 프로퍼티 바인딩을 해줍니다.
 */
UCLASS()
class GASEXTENSION_API UGEAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

protected:
    FGameplayTagContainer TagsToRegister;

private:
    TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

public:
    virtual void NativeInitializeAnimation() override;

protected:
    UFUNCTION()
    virtual void OnGameplayEffectTagCountChanged_Event(const FGameplayTag Tag, int32 NewCount);

    UFUNCTION(BlueprintPure)
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem.Get(); }
};
