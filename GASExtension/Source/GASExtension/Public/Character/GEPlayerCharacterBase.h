// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GECharacterBase.h"
#include "GameplayTags.h"
#include "GEPlayerCharacterBase.generated.h"

class UInputAction;
class UGEInputConfig;
class UInputMappingContext;

/*
 * 입력 태그를 활용한 입력 액션과 게임플레이 어빌리티 바인딩 기능이 포함되어 있는 캐릭터 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API AGEPlayerCharacterBase : public AGECharacterBase
{
    GENERATED_BODY()

    // Ability 입력 설정을 위한 데이터 에셋입니다.
    UPROPERTY(EditAnywhere, Category = "Config|Input|Ability")
    TObjectPtr<UGEInputConfig> AbilityInputConfig;

    // AbilityInputConfig에 등록된 입력 액션 에셋이 설정된 입력 매핑 컨텍스트입니다.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Input|Ability", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> AbilityInputMappingContext;

    // AbilityInputConfig로부터 캐싱된 맵입니다.
    TMap<TObjectPtr<UInputAction>, FGameplayTag> AbilityInputMap;

public:
    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    UFUNCTION(BlueprintCallable)
    virtual void AddMappingContext(UInputMappingContext* InputMappingContext, int32 Priority = 0);

    // 향상된 입력 컴포넌트 설정
    virtual void SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent);

private:
    void SetupAbilityInputConfig(UEnhancedInputComponent* EnhancedInputComponent);

    void OnInputActionPressed(UInputAction* InputAction);

    void OnInputActionReleased(UInputAction* InputAction);
};
