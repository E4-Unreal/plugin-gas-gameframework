// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GGFAttributesPresenterBase.generated.h"

/* 헤더 매크로 */

// Attribute Setter 선언
#define DECLARE_ATTRIBUTE_SETTER(AttributeName) virtual void Set##AttributeName(float Value){ };

// Attribute Value Change 이벤트 핸들링 델리게이트 및 메서드 선언
#define DECLARE_ATTRIBUTE_VALUE_CHANGE_HANDLE(AttributeName) \
    FDelegateHandle On##AttributeName##AttributeValueChangeHandle;  \
    void On##AttributeName##AttributeValueChange_Event(const FOnAttributeChangeData& Data);

/* CPP 매크로 */

// Attribute Value Change 이벤트 핸들링 메서드 정의
#define DEFINE_ATTRIBUTE_VALUE_CHANGE_HANDLE(ClassName, AttributeName) \
    void ClassName##::On##AttributeName##AttributeValueChange_Event(const FOnAttributeChangeData& Data)   \
    {   \
        Set##AttributeName(Data.NewValue);  \
    }

// GetAttributeValues에서 사용
#define UPDATE_ATTRIBUTE_VALUE(AttributeSetClass, AttributeName) \
    AttributeValue = GetAbilitySystem()->GetGameplayAttributeValue(AttributeSetClass##::Get##AttributeName##Attribute(), bFound);   \
    if(bFound) Set##AttributeName(AttributeValue);

// Attribute Value Change 이벤트 바인딩
#define BIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(ClassName, AttributeName)  \
    GetAbilitySystem()->GetGameplayAttributeValueChangeDelegate(ClassName::Get##AttributeName##Attribute())   \
    .AddUObject(this, &ThisClass::On##AttributeName##AttributeValueChange_Event);

// Attribute Value Change 이벤트 언바인딩
#define UNBIND_ATTRIBUTE_VALUE_CHANGE_DELEGATE(ClassName, AttributeName)  \
    GetAbilitySystem()->GetGameplayAttributeValueChangeDelegate(ClassName::Get##AttributeName##Attribute())   \
    .Remove(On##AttributeName##AttributeValueChangeHandle);

class UAbilitySystemComponent;
struct FOnAttributeChangeData;

/**
 * Attribute를 UI에 바인딩하기 위한 Presenter 클래스입니다.
 * 작성 편의를 위한 각종 매크로가 포함되어 있으며 사용 예시는 GGFHealthAttributesPresenterBase 클래스를 참고하시면 됩니다.
 */
UCLASS()
class GASGAMEFRAMEWORK_API UGGFAttributesPresenterBase : public UUserWidget
{
    GENERATED_BODY()

protected:

    /* 매크로에서 사용하기 위한 임시 변수 */
    bool bFound;
    float AttributeValue;

private:

    UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetAbilitySystem, meta = (AllowPrivateAccess = true))
    UAbilitySystemComponent* AbilitySystem;

public:
    UFUNCTION(BlueprintSetter)
    void SetAbilitySystem(UAbilitySystemComponent* InAbilitySystem);

protected:
    FORCEINLINE UAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }

    // 초기화를 위해 현재 Attribute 값을 가져옵니다.
    virtual void GetAttributeValues();

    // 이벤트 핸들링 메서드를 바인딩합니다.
    virtual void BindAttributeValueChangeEvents();

    // 이벤트 핸들링 메서드를 언바인딩합니다.
    virtual void UnBindAttributeValueChangeEvents();
};
