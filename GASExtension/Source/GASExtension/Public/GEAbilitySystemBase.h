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

    // AbilitySystem 에서 기본으로 사용할 AttributeSet 목록입니다.
    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UAttributeSet>> DefaultAttributes;

    // 기본 AttributeSet 을 초기화하기 위한 GameplayEffect 목록입니다.
    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

    // 게임 시작 후 적용할 GameplayEffect 목록입니다. ex) 리스폰 후 일정 시간 무적
    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
    TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

protected:
    /* UActorComponent */

    virtual void OnRegister() override;
    virtual void BeginPlay() override;

    /* 메서드 */

    // 여러 AttributeSet 을 생성하고 등록합니다.
    UFUNCTION(BlueprintCallable, Category = "GEAbilitySystemBase")
    void CreateAttributes(const TArray<TSubclassOf<UAttributeSet>>& AttributeClasses);

    // 단일 AttributeSet 을 생성하고 등록합니다.
    UFUNCTION(BlueprintCallable, Category = "GEAbilitySystemBase")
    void CreateAttribute(const TSubclassOf<UAttributeSet> AttributeClass);

    // 여러 GameplayEffect 를 적용합니다.
    UFUNCTION(BlueprintCallable, Category = "GEAbilitySystemBase")
    void ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectClasses);

    // 단일 GameplayEffect 를 적용합니다.
    UFUNCTION(BlueprintCallable, Category = "GEAbilitySystemBase")
    void ApplyEffect(const TSubclassOf<UGameplayEffect> EffectClass);

private:
    // AttributeSet 설정 및 초기화
    void InitializeAttributes();
};
