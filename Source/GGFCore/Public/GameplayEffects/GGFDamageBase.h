// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GGFDamageBase.generated.h"

class UTargetTagRequirementsGameplayEffectComponent;

/**
 * 데미지 전용 게임플레이 이펙트 클래스
 */
UCLASS()
class GGFCORE_API UGGFDamageBase : public UGameplayEffect
{
    GENERATED_BODY()

public:
    /* 서브 오브젝트 이름 */

    static FName TargetTagRequirementsComponentName;

private:
    /* 컴포넌트 */

    UPROPERTY(BlueprintGetter = GetTargetTagRequirementsComponent, Category = "Component")
    TObjectPtr<UTargetTagRequirementsGameplayEffectComponent> TargetTagRequirementsComponent;

public:
    UGGFDamageBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UTargetTagRequirementsGameplayEffectComponent* GetTargetTagRequirementsComponent() const { return TargetTagRequirementsComponent; }
};
