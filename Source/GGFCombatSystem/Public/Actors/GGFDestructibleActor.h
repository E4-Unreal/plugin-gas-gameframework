// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GEDamageableActor.h"
#include "GGFDestructibleActor.generated.h"

UCLASS()
class GGFCOMBATSYSTEM_API AGGFDestructibleActor : public AGEDamageableActor
{
    GENERATED_BODY()

    /* 컴포넌트 */

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetDisplayMesh, Category = "Component")
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

public:
    AGGFDestructibleActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    /* DamageableActor */

    virtual void OnDead_Implementation() override;

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
};
