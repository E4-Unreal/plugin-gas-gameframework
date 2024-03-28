// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GGFAbilitySystemBase.generated.h"

/**
 * 모든 Ability System 클래스의 기저 클래스입니다.
 *
 * AttributeSet 설정 및 초기화를 진행합니다.
 * 게임 시작 후 적용할 GameplayEffect 를 설정할 수 있습니다.
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class GASGAMEFRAMEWORK_API UGGFAbilitySystemBase : public UAbilitySystemComponent
{
    GENERATED_BODY()

protected:
    // 기본으로 사용할 AttributeSet 목록입니다.
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TSubclassOf<UAttributeSet>> DefaultAttributes;

    // 기본으로 적용시킬 GameplayEffect 목록입니다.
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

    // 기본으로 부여할 GameplayAbility 목록입니다.
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

public:
    /* UActorComponent */
    UGGFAbilitySystemBase();

    virtual void InitializeComponent() override;

    /* API */

    // 입력 태그로 Ability를 Press합니다.
    UFUNCTION(BlueprintCallable, Category = "GGFAbilitySystemBase")
    void PressInputTag(FGameplayTag InputTag);

    // 입력 태그로 Ability를 Release합니다.
    UFUNCTION(BlueprintCallable, Category = "GGFAbilitySystemBase")
    void ReleaseInputTag(FGameplayTag InputTag);

    // 마지막으로 추가된 Ability만 Press합니다.
    virtual void AbilityLocalInputPressed(int32 InputID) override;

    // 마지막으로 추가된 Ability만 Release합니다.
    virtual void AbilityLocalInputReleased(int32 InputID) override;

protected:
    // Ability InputTag가 설정된 Ability의 경우 InputID를 설정합니다.
    virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

    // 체력 어트리뷰트가 0이 되었을 때 호출되는 이벤트입니다.
    UFUNCTION(BlueprintNativeEvent)
    void OnDead();

private:
    // AttributeSet 설정 및 초기화
    void InitializeAbilitySystem();

    // 체력 어트리뷰트 값 변경 이벤트 바인딩
    void BindHealthAttributeDelegate();
};
