// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGFDestructibleActor.h"
#include "GGFExplosiveObject.generated.h"

class UGGFExplosiveComponent;
class USphereComponent;

/**
 * 데미지를 입으면 폭발하는 오브젝트 클래스입니다.
 */
UCLASS()
class GGFCOMBATSYSTEM_API AGGFExplosiveObject : public AGGFDestructibleActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetExplosionArea, Category = "Component")
    TObjectPtr<USphereComponent> ExplosionArea;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetExplosiveComponent, Category = "Component")
    TObjectPtr<UGGFExplosiveComponent> ExplosiveComponent;

public:
    AGGFExplosiveObject();

    /* Actor */

    virtual void Destroyed() override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    USphereComponent* GetExplosionArea() const { return ExplosionArea; }

    UFUNCTION(BlueprintGetter)
    UGGFExplosiveComponent* GetExplosiveComponent() const { return ExplosiveComponent; }
};
