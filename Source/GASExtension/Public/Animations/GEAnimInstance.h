// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "GEAnimInstance.generated.h"

/**
 * GAS 전용 애님 인스턴스 클래스로 게임플레이 태그 탈부착 이벤트와 애니메이션 블루프린트 변수 간의 바인딩 기능이 포함되어 있습니다.
 */
UCLASS()
class GASEXTENSION_API UGEAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

    /* 레퍼런스 */

    TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

public:
    virtual void NativeInitializeAnimation() override;

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem.Get(); }
};
