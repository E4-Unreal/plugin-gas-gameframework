// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GEAbilitySystemBase.generated.h"

/**
 * 모든 Ability System 클래스의 기저 클래스입니다.
 *
 * AttributeSet 설정 및 초기화를 진행합니다.
 * 게임 시작 후 적용할 GameplayEffect 를 설정할 수 있습니다.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class GASEXTENSION_API UGEAbilitySystemBase : public UAbilitySystemComponent
{
    GENERATED_BODY()

    // 기본으로 사용할 AttributeSet 목록입니다.
    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UAttributeSet>> DefaultAttributes;

    // 기본으로 부여할 GameplayAbility 목록입니다.
    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

protected:
    /* UActorComponent */
    UGEAbilitySystemBase();

    virtual void InitializeComponent() override;

    /* 메서드 */

    // AttributeSets를 생성하고 등록합니다.
    void CreateAttributes(const TArray<TSubclassOf<UAttributeSet>>& AttributeClasses);

    // AttributeSet을 생성하고 등록합니다.
    void CreateAttribute(const TSubclassOf<UAttributeSet> AttributeClass);

private:
    // AttributeSet 설정 및 초기화
    void InitializeAttributes();

    // 기본 Abilities를 부여합니다.
    void GiveDefaultAbilities();
};
