// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTags.h"
#include "GEAbilityInputBinder.generated.h"

class UGEAbilitySystemBase;
class UGEInputConfig;
class UInputAction;

// TODO 블루프린트 호환
/*
 * 입력 태그를 매개 변수로 어빌리티 전용 입력 에셋과 대응하는 어빌리티를 바인딩하는 컴포넌트입니다.
 * GEAbilitySystemBase를 서브 오브젝트로 가진 캐릭터 클래스에서만 사용할 수 있습니다.
 * 해당 캐릭터 클래스의 SetupPlayerInputComponent에서 BindAbilityInput를 호출해주어야 합니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGEAbilityInputBinder : public UActorComponent
{
    GENERATED_BODY()

    TWeakObjectPtr<UGEAbilitySystemBase> AbilitySystem;

    // 어빌리티 전용 입력 에셋 등록을 위한 데이터 에셋
    UPROPERTY(EditAnywhere, Category = "Config")
    TObjectPtr<UGEInputConfig> AbilityInputConfig;

    // 등록된 어빌리티 전용 입력 에셋
    TMap<TObjectPtr<UInputAction>, FGameplayTag> RegisteredAbilityInput;

public:
    UGEAbilityInputBinder();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    void BindAbilityInput(UEnhancedInputComponent* EnhancedInputComponent);

private:
    // 어빌리티 전용 입력 에셋 등록
    void RegisterAbilityInputConfig();

    void PressInputAction(UInputAction* InputAction);

    void ReleaseInputAction(UInputAction* InputAction);
};
