// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GECharacter.h"
#include "GEPlayerCharacter.generated.h"

class UGEInputManager;

UCLASS()
class GASEXTENSION_API AGEPlayerCharacter : public AGECharacter
{
    GENERATED_BODY()

public:
    // InputManager 서브 오브젝트 이름
    static FName InputManagerName;

private:
    /* 컴포넌트 */

    // 어빌리티 전용 입력 바인딩을 위한 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetInputManager, Category = "Component")
    TObjectPtr<UGEInputManager> InputManager;

public:
    AGEPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /* Pawn */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    // 향상된 입력 컴포넌트 설정
    virtual void SetupEnhancedInputComponent(UEnhancedInputComponent* EnhancedInputComponent);

protected:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE UGEInputManager* GetInputManager() const { return InputManager; }
};
