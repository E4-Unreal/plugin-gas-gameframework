// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GECharacterBase.h"
#include "GEPlayerCharacterBase.generated.h"

class UGEAbilityInputBinder;
class UInputMappingContext;

/*
 * 입력 태그를 활용한 입력 액션과 게임플레이 어빌리티 바인딩 기능이 포함되어 있는 캐릭터 클래스입니다.
 */
UCLASS()
class GASEXTENSION_API AGEPlayerCharacterBase : public AGECharacterBase
{
    GENERATED_BODY()

    /* 컴포넌트 */
    // 어빌리티 전용 입력 바인딩을 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Component")
    TObjectPtr<UGEAbilityInputBinder> AbilityInputBinder;

    /* 설정 */
    // 기본 입력 매핑 컨텍스트 목록
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

public:
    AGEPlayerCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Actor */
    virtual void BeginPlay() override;

    /* Pawn */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    // 향상된 입력 컴포넌트 설정
    virtual void SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent);
};
