// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GEAbilitySystem.generated.h"

/**
 * 모든 Ability System 클래스의 기저 클래스입니다.
 *
 * AttributeSet 설정 및 초기화를 진행합니다.
 * 게임 시작 후 적용할 GameplayEffect 를 설정할 수 있습니다.
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class GASEXTENSION_API UGEAbilitySystem : public UAbilitySystemComponent
{
    GENERATED_BODY()

protected:
    // 기본으로 사용할 AttributeSet 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UAttributeSet>> DefaultAttributes;

    // 기본으로 사용할 Stats 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UAttributeSet>> DefaultStats;

    // 기본으로 적용시킬 GameplayEffect 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

    // 기본으로 부여할 GameplayAbility 목록입니다.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

public:
    UGEAbilitySystem();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    // 서버 전용 컴포넌트 초기화 이벤트
    UFUNCTION(BlueprintNativeEvent)
    void ServerInitializeComponent();

protected:
    // 기본 설정 및 초기화
    virtual void InitializeAbilitySystem();
};
